# Trustee: Full Privacy Preserving Sealed-bid Auction on top of Ethereum

## Components
1. Enclave (C)
2. EnclaveLink (C++)
3. ManagedEnclave (C++/CLI)
4. App (C#)
5. Auction (Solidity)

## Requirements
1. [Visual Studio 2017](https://visualstudio.microsoft.com/downloads/) (make sure to mark on C/C++, C#, and Windows SDK 8.1)
2. [Truffle Ganache](https://truffleframework.com/ganache)
3. [Solc](https://github.com/ethereum/solidity/releases)
4. [Intel SGX-SDK](https://software.intel.com/en-us/sgx-sdk)

## Build
1. Open Trustee.sln with Visual Studio 2017
2. Set App as the startup project
3. Extract Solc archive into the directory Trustee\Win32
4. Build the solution

## Run
Run Ganache with more than 50 accounts and set port on 8545
Run the App which starts the following scenario
1. Trustee deploys the smart contract on Ganache
2. It initializes the enclave, generating new keys and account
3. The auctioneer account (first account) will send a deposit (5 eth) to the Enclave account
4. The auctioneer starts the auction specifying the intervals and initial deposit
5. 50 bidders will randomly generate bids and submit the encrypted bids to the smart contract
6. The Enclave will retrieve the encrypted bids, determine the winner, and send a transaction
7. The smart contract verifies the hash on the input submitted by the Enclave for consistency
8. The winner is set and the losing bidder and the auctioneer start refunding their initial deposit
9. Another stage (Future work) is set to reclaim the bid value from the winner
