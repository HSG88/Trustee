#pragma once
typedef unsigned char Commit;
typedef unsigned char Bid;
const int MAX_BIDDERS = 10;
int ValidCommitment(Commit, Bid);
int IsGreater(Bid, Bid);
void AuctionWinner(Commit commits[MAX_BIDDERS], Bid winner, Bid bids[MAX_BIDDERS], int * output);
