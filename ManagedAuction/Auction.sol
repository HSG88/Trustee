pragma solidity ^0.4.24;

contract Auction {
    address public constant SGXADDRESS= ADDRESSPLACEHOLDER;
    bytes32 public constant SGXDHPUBLICKEY = DHPLACEHOLDER;
    uint public bidEnd;
    uint public withdrawEnd;
    uint public initialDeposit;
    uint16 public winnerIndex;
    uint32 public winnerBid;
    
    struct Bid {
        bytes32 bidCipher;
        bytes32 ecdhPublicKey;
    }
    mapping(address => Bid) public bidders;
    address[] public index;
    
    constructor(uint _bidInterval, uint _sgxInterval, uint _initialDeposit) public {
        bidEnd = block.number + _bidInterval;
        withdrawEnd = bidEnd+_sgxInterval;
        initialDeposit = _initialDeposit;
    }
	function getIndexLength() public view returns(uint) {
		return index.length;
	}
    function submitBid(bytes32 cipher, bytes32 key) public payable{
        //require(block.number < bidEnd);
        require(msg.value == initialDeposit);
        require(bidders[msg.sender].bidCipher==0); //one time bidding only
        index.push(msg.sender);
        bidders[msg.sender] = Bid(cipher, key);
    }
    function setWinner(bytes32 _inputHash, uint16 _winnerIndex, uint32 _winnerBid) public {
        require(msg.sender == SGXADDRESS);
        //require(block.number > bidEnd);
        //require(block.number < withdrawEnd);
        bytes memory data = new bytes(index.length * 64);
        for(uint i =0; i< index.length; i++)
            {
                for(uint j = 0; j< 32; j++)
                {
                    data[i*64 +j] = bidders[index[i]].bidCipher[j];
                    data[i*64+32+j] = bidders[index[i]].ecdhPublicKey[j];
                }
            }
        require(_inputHash == keccak256(data));
        winnerBid = _winnerBid;
        winnerIndex = _winnerIndex;
    }
    function withdrawDeposit() public {
        //require(block.number > withdrawEnd);
        require(bidders[msg.sender].bidCipher != "0x0");
        require(index[winnerIndex] != msg.sender); //winner can't withdraw
        delete bidders[msg.sender];
        msg.sender.transfer(initialDeposit);
    }
}