#include "Source.h"
void AuctionWinner(Commit commits[MAX_BIDDERS], Bid winner, Bid bids[MAX_BIDDERS], int* output)
{	
	Bid max = 0;
	*output = 0;
	for (int i = 0; i < MAX_BIDDERS; i++)
	{
		if (!ValidCommitment(commits[i], bids[i]))
			return;
		if (bids[i] > max)
			max = bids[i];
	}
	*output = max == winner;
}