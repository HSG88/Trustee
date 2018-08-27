var Web3 = require('web3');
var {sha3} = require('ethereumjs-util')


var web3 = new Web3();
web3.setProvider(new web3.providers.HttpProvider('http://localhost:7545'))
var AuctionContract = web3.eth.contract(JSON.parse('[{"constant":true,"inputs":[],"name":"SGXADDRESS","outputs":[{"name":"","type":"address"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"hash","outputs":[{"name":"","type":"bytes32"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[{"name":"","type":"uint256"}],"name":"index","outputs":[{"name":"","type":"address"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"bidsCount","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"SGXDHPUBLICKEY","outputs":[{"name":"","type":"bytes32"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"data","outputs":[{"name":"","type":"bytes"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[],"name":"getHash","outputs":[{"name":"","type":"bytes32"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[{"name":"","type":"address"}],"name":"bidders","outputs":[{"name":"bidCipher","type":"bytes32"},{"name":"ecdhPublicKey","type":"bytes32"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"cipher","type":"bytes32"},{"name":"key","type":"bytes32"}],"name":"submitBid","outputs":[],"payable":false,"stateMutability":"nonpayable","type":"function"}]'))
var contract = AuctionContract.at('820f478c6dc42cf80b295D3b9234Ad66Ec6e77B4')

console.log(contract.getHash.call({from: web3.eth.accounts[6], gas:3000000}))
/*var count = Number(contract.bidsCount().toString(10))
console.log("Number of bidders: "+count)
console.log("Reading submitted bids")
var s =""
for(var i =0; i< count; i++)
{
    var address = contract.index(i);
    var data = contract.bidders(address)
    console.log("Address: "+address)
    console.log("Cipher: "+data[0].slice(2))
    console.log("ECHD Public Key: "+data[1].slice(2))
    s+=data[0].slice(2)
    s+=data[1].slice(2)
}
console.log("Data: "+s)
console.log("Hash: "+sha3(Buffer.from(s,'hex')).toString('hex'))

//console.log(contract.bidsCount().toString(10))
//console.log(web3.sha3('0x4ad8ecd2bfa9f73466580f0b0a9f45b3d2a0466bbf576d1b5575d2a15109ab482bf30d591361a03f2ff86dbc0e6a42790e516d67f013e75a46d0eebacde021fbb846e29ae0560f81201dbc0841fe2e012a72aba517479d62e97fba73a5a9551820829eece31d482ea3f9a3a93c7808742c7309471fad6778ebd61b1f91eae0629a8515e4660f511f3811f2016523671dfe88c3c8451dae4f7f41ae47069a3f7c311bbf784e02e989a48a3f6319305cc95868a43fe60b0bcda1835591c8c005be', {encoding:"hex"}))*/