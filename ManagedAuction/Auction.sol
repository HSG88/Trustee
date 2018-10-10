pragma solidity ^0.4.24;
contract Auction {
    bytes32[] public bids;
    bytes32 public PublicKey;
    mapping(address => uint) public ledger;
    address public Auctioneer;
    address public Enclave;
    uint public T1;
    uint public T2;
    uint public T3;
    uint public T4;
    uint public D;
    address public WinnerAddress;
    uint32 public WinnerBid;
    bytes32 public Hash;
    enum State {INIT, BID, REVEAL, DISPUTE}
    State public state;

    constructor() public {
        Auctioneer = msg.sender;
    }
	function StartAuction(address _enclave, bytes32 _publickey, uint _t1, uint _t2, uint _t3, uint _t4, uint _d) public payable
	{
	    require(state == State.INIT);
	    require(msg.sender == Auctioneer);
	    require(msg.value == _d);
	    T1 = block.number + _t1;
	    T2 = T1 + _t2;
	    T3 = T2 + _t3;
	    T4= T3 + _t4;
	    D = _d;
        ledger[msg.sender] = msg.value;
        Enclave = _enclave; 
        PublicKey = _publickey;
	    state = State.BID;
	}
	function GetLength() public view returns(uint){
	    return bids.length;
	}
    function SubmitBid(bytes32 cipher, bytes32 key) public payable{
        require(state == State.BID);
        require(block.number < T1);
        require(msg.value == D);
        ledger[msg.sender] = msg.value;
        bids.push(cipher);
        bids.push(key);
        bids.push(bytes32(msg.sender));
    }
    function SetWinner(bytes32 _inputHash, address _winnerAddress, uint32 _winnerBid) public {
        require(state == State.BID);
        require(block.number > T1);
        require(block.number < T2);
        require(msg.sender == Enclave);
        Hash = _inputHash;
        WinnerBid = _winnerBid;
        WinnerAddress = _winnerAddress;
        state = State.REVEAL;
    }
    function Dispute() public
    {
        require(state == State.REVEAL);
        require(block.number > T2);
        require(block.number < T3);
        if(Hash !=keccak256(abi.encodePacked(bids)))
            {
                state = State.DISPUTE;
                ledger[msg.sender] += ledger[Auctioneer];
                ledger[Auctioneer] = 0;
            }
    }
    function Refund() public {
        require(block.number > T3);
        require(block.number < T4);
        require((state == State.REVEAL && msg.sender != WinnerAddress) || (state == State.DISPUTE && msg.sender != Auctioneer));
        require(ledger[msg.sender] != 0);
        uint balance = ledger[msg.sender];
        delete ledger[msg.sender];
        msg.sender.transfer(balance);
    }
    function Reset() public {
        require(msg.sender == Auctioneer);
        require(block.number > T4);
        state = State.INIT;
        bids.length = 0;
        Auctioneer.transfer(address(this).balance);
    }
}