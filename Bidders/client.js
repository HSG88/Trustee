var EC = require('elliptic')
var crypto = require('crypto')
var Web3 = require('web3');

var web3 = new Web3();
web3.setProvider(new web3.providers.HttpProvider('http://localhost:7545'))
var AuctionContract = web3.eth.contract(JSON.parse('[{"constant":true,"inputs":[],"name":"SGXADDRESS","outputs":[{"name":"","type":"address"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"hash","outputs":[{"name":"","type":"bytes32"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[{"name":"","type":"uint256"}],"name":"index","outputs":[{"name":"","type":"address"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"bidsCount","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"SGXDHPUBLICKEY","outputs":[{"name":"","type":"bytes32"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"data","outputs":[{"name":"","type":"bytes"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[],"name":"getHash","outputs":[{"name":"","type":"bytes32"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[{"name":"","type":"address"}],"name":"bidders","outputs":[{"name":"bidCipher","type":"bytes32"},{"name":"ecdhPublicKey","type":"bytes32"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"cipher","type":"bytes32"},{"name":"key","type":"bytes32"}],"name":"submitBid","outputs":[],"payable":false,"stateMutability":"nonpayable","type":"function"}]'))
var contract = AuctionContract.at('820f478c6dc42cf80b295D3b9234Ad66Ec6e77B4')


var sgxECDHPublicKey = contract.SGXDHPUBLICKEY().toString().slice(2)
console.log("Retrieved SGX ECDH Public Key: "+sgxECDHPublicKey)
for (var i = 4; i < 7; i++) 
{
    var bid = 1000*i
    var plainData = Buffer.alloc(4)
    plainData.writeUInt32LE(bid, 0)

    var ec = new EC.ec('curve25519')
    var bidderKey = ec.genKeyPair();
    var shared = bidderKey.derive(ec.keyFromPublic(sgxECDHPublicKey, 'hex').getPublic());

    var aesKey = shared.toBuffer().slice(0, 16);
    var iv = Buffer.alloc(12);


    crypto.randomFillSync(iv);
    var cipher = crypto.createCipheriv('aes-128-gcm', aesKey, iv)
    var output1 = cipher.update(plainData)
    cipher.final();
    var tag = cipher.getAuthTag()
    var bidCipher = Buffer.concat([tag, iv, output1]).toString('hex')
    var ecdhPublicKey = bidderKey.getPublic('hex')

    contract.submitBid('0x' + bidCipher, '0x' + ecdhPublicKey, { from: web3.eth.accounts[i], gas: 3000000 })

    console.log("Submitting bid"+bid)
    console.log("Account: "+web3.eth.accounts[i])
    console.log("Cipher: "+bidCipher)
    console.log("PublicKey: "+ecdhPublicKey)
}