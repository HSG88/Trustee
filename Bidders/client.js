var EC = require('elliptic')
//var gcm = require('node-aes-gcm')
var ec = new EC.ec('curve25519')
const crypto = require('crypto')

const sgxPublicKey = '513F0F8003F342EA1417FA1DF7CE7E332B7668E46F28A78087D5BC54EF788FBD'
var bid = 5000
var plainData = Buffer.alloc(4)
plainData.writeUInt32LE(bid,0)

var bidderKey = ec.genKeyPair();
var shared = bidderKey.derive(ec.keyFromPublic(sgxPublicKey, 'hex').getPublic());

var aesKey = shared.toBuffer().slice(0,16);
var iv = Buffer.alloc(12);


crypto.randomFillSync(iv);
var cipher = crypto.createCipheriv('aes-128-gcm',aesKey,iv)
var output1 = cipher.update(plainData)
cipher.final();
var tag = cipher.getAuthTag()

console.log("ECDH Public: "+bidderKey.getPublic('hex').toUpperCase())
console.log("Shared key: " +shared.toString('hex').toUpperCase())
console.log("Plain :"+ plainData.toString('hex').toUpperCase())
console.log("IV :"+ iv.toString('hex').toUpperCase())
console.log("Key :"+ aesKey.toString('hex').toUpperCase())
console.log("Cipher :"+ output1.toString('hex').toUpperCase())
console.log("Tag :"+ tag.toString('hex').toUpperCase())
console.log("Final Cipher: "+ Buffer.concat([tag,iv,output1]).toString('hex').toUpperCase())

