pragma solidity ^0.4.18;

contract Simple {
    uint public number;
    address sgxAddress;
    constructor() public {
        sgxAddress = msg.sender;
    }
    function Store(uint _number) public{
        require(msg.sender == sgxAddress);
        number = _number;
    }
    function Retrieve() public view returns(uint) {
        return number;
    }
}