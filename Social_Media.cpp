#include<bits/stdc++.h>
using namespace std;


class Player{
    private:
        string name;
        string role;
        int basePrice;
        int soldPrice;
        string team;
        bool sold;
        vector<int>bidHistory;
    public:
        Player(string name,string role,int basePrice)
        :name(name),role(role),basePrice(basePrice),soldPrice(0),team("Unsold"),sold(false){}

        void setSoldPrice(int price){
            soldPrice=price;
            sold=true;
        }

        void setTeam(string teamName){
            team=teamName;
        }

        int getBasePrice(){
           return basePrice;
        }

        int getSoldPrice(){
          return soldPrice;
        }

        string getName(){
            return name;
        }

        string getRole(){
            return role;
        }

        string getTeam(){
            return team;
        }

        bool isSold(){
            return sold;
        }

        void addBidHistory(int bid){
            bidHistory.push_back(bid);
        }

        void displayBidHistory(){
            cout<<"\tBid History"<<endl;
            for(auto it:bidHistory){
                cout<<it<<" ";
            }
            cout<<endl;
        }

};

class Team{
    private:
        string name;
        int budget;
        int maxPlayer;
        int currentPlayer;
        vector<Player>squad;
    
    public:
        Team(string name,int budget,int maxPlayer,int currentPlayer):
        name(name),budget(budget),maxPlayer(maxPlayer),currentPlayer(currentPlayer){}

        bool bid(Player &player,int bidAmount){
            if(budget>=bidAmount && currentPlayer<maxPlayer){
                budget-=bidAmount;
                player.setSoldPrice(bidAmount);
                player.setTeam(name);
                player.addBidHistory(bidAmount);
                squad.push_back(player);
                currentPlayer++;
                return true;
            }
            return false;
        }

        int getBudget(){
            return budget;
        }

        vector<Player>getSquad(){
            return squad;
        }

        string getName(){
            return name;
        }

        int getCurrentPlayer(){
            return currentPlayer;
        }

        int getMaxPlayer(){
            return maxPlayer;
        }

        void displayTeam(){
            cout<<"Team: "<<name<<"\nBudget Left: "<<budget<<"\nPlayers:\n";
            for(auto player:squad){
                cout<<player.getName()<<"\t"<<player.getRole()<<"\t"<<player.getSoldPrice()<<endl;
            }
        }
};

class Auctioneer{
    private:
        vector<Player>players;
        vector<Team>teams;
    public:
        Auctioneer(vector<Player>playerList,vector<Team>teamList):
        players(playerList),teams(teamList){}
    
        void startAuction(){
            for(auto player:players){
                if(!player.isSold()){
                    auction(player);
                }
            }
        }

        void auction(Player &player){
                int highestBid=player.getBasePrice();
                Team*highestBidder=NULL;
                vector<pair<Team*,int>>bidTable;

               // unordered_map<Team*,int>bidTable;

                for(auto &team:teams){
                    if(team.getBudget()>player.getBasePrice() && team.getMaxPlayer()>team.getCurrentPlayer()){
                        int bidAmount;
                        cout<<team.getName()<<" , Enter your bid price for "<<player.getName()<<" (Base Price: "
                        <<player.getBasePrice()<<"): ";
                        cin>>bidAmount;
                        if(bidAmount>=highestBid && bidAmount<=team.getBudget()){
                           bidTable.push_back({&team,bidAmount});
                        }
                    }
                }

                if(!bidTable.empty()){
                    for(auto bid:bidTable){
                    if(bid.second>highestBid){
                        highestBid=bid.second;
                        highestBidder=bid.first;
                    }
                }

                if(highestBidder!=NULL && highestBidder->bid(player,highestBid)){
                    announceWinner(player,*highestBidder);
                }else{
                    cout<<player.getName()<<" remains unsold\n";
                }
             }
        }


        void announceWinner(Player &player,Team &team){
            cout<<"\n Player "<<player.getName()<<" is sold to "<<team.getName()<<" for "<<player.getSoldPrice()<<"\n\n";
        }

        void diaplayUnsoldPlayer(){
            cout<<"\n\t List of unsold Players\n";
            for(auto player:players){
                if(!player.isSold())
                    cout<<player.getName()<<" ( "<<player.getRole()<<" ) "<<player.getBasePrice()<<"\n";
            }
            cout<<endl;
        }

        void displayTeamSummary(){
            for(auto team:teams){
                team.displayTeam();
            }
        }
};



 int main(){


    vector<Player>players={
        Player("Virat","Batsman",200),
        Player("Rohit", "Batsman", 180),
        Player("Jasprit", "Bowler", 220),
        Player("Ravindra", "All-Rounder", 160),
        Player("Shreyas", "Batsman", 140),
        Player("KL Rahul", "Wicketkeeper", 190),
        Player("Hardik", "All-Rounder", 210),
        Player("Shami", "Bowler", 170)

    };
    vector<Team>teams={
        Team("Mumbai",500,3,0),
        Team("Chennai",600,3,0)
    };

    Auctioneer auction(players,teams);
    auction.startAuction();
    auction.diaplayUnsoldPlayer();
    auction.displayTeamSummary();

    return 0;
}
