pragma solidity ^0.5.0;
contract Auction {
    bytes32[] public bids;
    bytes32 public PublicKey;
    mapping(address => uint) public ledger;
    uint public T1;
    uint public T2;
    uint public T3;
    uint public D;
    address payable public  Auctioneer;
    address public Enclave;
    address public WinnerAddress;
    address[] public bidders;
    enum State {INIT, BID, REVEAL, MALICIOUS}
    State public state;
    uint32 public WinnerBid;

    constructor() public {
        Auctioneer = msg.sender;
    }
	function StartAuction(address _enclave, bytes32 _publickey, uint _t1, uint _t2, uint _t3,uint _d) public payable
	{
	    require(state == State.INIT);
	    require(msg.sender == Auctioneer);
	    require(msg.value == _d);
	    T1 = block.number + _t1;
	    T2 = T1 + _t2;
	    T3 = T2 + _t3;
	    D = _d;
        ledger[Auctioneer] = msg.value;
        Enclave = _enclave; 
        PublicKey = _publickey;
	    state = State.BID;
	}
	function GetLength() public view returns(uint){
	    return bids.length;
	}
    function SubmitBid(bytes32 cipher, bytes32 key) public payable{
        require(state == State.BID  && msg.value == D && bidders.length < 2**32);
        //require(block.number < T1);
        bidders.push(msg.sender);
        ledger[msg.sender] = msg.value;
        bids.push(cipher);
        bids.push(key);
    }
    function SetWinner(bytes32 _inputHash, uint32 _winnerIndex, uint32 _winnerBid) public {
        require(state == State.BID && msg.sender == Enclave);
        //require((block.number > T1 && block.number < T2 );
        if(_inputHash == keccak256(abi.encodePacked(bids)))
        {
            WinnerBid = _winnerBid;
            WinnerAddress = bidders[_winnerIndex];
            state = State.REVEAL;
        }
        else
        state = State.MALICIOUS;
    }
    function Refund() public {
        //require((block.number > T2 && block.number < T3);
        require((state == State.REVEAL && msg.sender != WinnerAddress) || (state == State.MALICIOUS && msg.sender != Auctioneer));
        require(ledger[msg.sender] != 0);
        uint balance = ledger[msg.sender];
        delete ledger[msg.sender];
        msg.sender.transfer(balance);
    }
    function Reset() public {
        require(msg.sender == Auctioneer);
        //require(block.number > T3);
        state = State.INIT;
        bids.length = 0;
        bidders.length = 0;
        WinnerBid = 0; 
        WinnerAddress = address(0);
        Auctioneer.transfer(address(this).balance);
    }
}