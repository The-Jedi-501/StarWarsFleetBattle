/* 
=============================================================
STAR WARS: FLEET BUILDER AND BATTLES
=============================================================

AUTHOR: Christopher DeMoura
Language: C++
Purpose: To create a project of which encompasses all of my knowledge so far of C++ into a project to further my understanding of those various functions within the code itslef

Code walkthrough and Goals: 
-Main idea is to essentially be given a list of ships adn user is prompted to pick 3 ships followed by picking to either randomize or select the opponents ships (Note the reason why the stats if you will are the same was for simplicty and essnelly Republic vs Seperatist iconic vehicles)
-After slecting "ship" they get stored into a vector for both player and enemey, now battle commences you take turns selecting your you want use and then the ship you wish to attack, a damage report will 
-the enemy will do the same via a randomizer functon to keep it beign very different, once either a player or enemys ships are depleted (vecotrs are empty) you either win or lose

-Please note there is alot of comments most are just notes I made along the way as you will see to either explain how a new piece of code worked or to show a new implemtentaion i had found that i found interesting and wanted to implement

Code topics used here and the purpose they served:
Classes --- Used to create the various "ships for the fleets (game mechanic)" which are just objects
Vectors --- A place in which needed to store information ie those objects themselves (vector a has ship 1 with all of its stats as well as ship 2 and its information)
Functions --- Used for repetive large chunks of code
BST --- Binary Search tree in the form of map reason for this over unordered map ie hash table was due to BST allowing a clean organized display
Randomizer --- Whilst not necessary from my lessons learnt was important for the code itself as well as the implementation itself
Basic Code functions (Loops, condiotional, variables, etc.) --- Its used literally everywhere 


*/

#include <iostream>
#include <vector> 
#include <unordered_map>
#include <map>

// #include <cstdlib> //this woudl be for old random ways
// #include <ctime>

#include <random> //This is the new way 

/*Goal of the code: I must creat a project that encompasses alot of the stuff we went over this weekend then upload to github
  Main Idea for the code: originally was goign to be a car based thing which we store cars adn race them against one another, might be modified to be star wars vehicles so doesnt mimic Dans code
  
  */


//phase 1- Get the classes set up to let the user input all those car --- since were ysing mulitple vcars uese vectors as the garage for storign all that then we have hash to actully acces all the LL stuff --- User inputs a car 
class Ship {
    public: //??? THIS MEANS will be modified view the code and or users later on 

        Ship(const int &current_pos, const std::string &name, const int &attack, const int &defense, const std::string &faction) { //THIS IS A CONSTRUCTO 
            this->current_pos = current_pos;
            this->name = name;
            this->attack = attack;
            this->defense = defense;
            this->faction = faction;
        }

        Ship() {//DO NOT DELETE THIS ITS A DUMB THING WHERE IT NEEDS A DEFAULT EVEN THOUGH I AM LITERLALLY NEVER USING IT 
            this->current_pos = 0;
            this->name = "";
            this->attack = 0;
            this->defense = 0;
            this->faction = "";
        }
        // Ship() { // WE ACANNOT DO SHIP_1 AS THIS IS A BUCNH OF CTONSTRUCTOR WE WANT OBJECT  --- can only ghave one of this not mulitple ie cannot copy past LAAT and another for ARC 
        //     this->name = "LAAT";
        //     this->horsePower = 200; //ATTK
        //     this->torque = 250; //Def
        // }
//this section mostly stripped from dan code just so i didnt have to rewrite
        int getCurrent_Pos() const {
            return this->current_pos;
        }

        std::string getName() const {
            return this->name;
        }
 
        int getAttack() const {
            return this->attack;
        }
 
        int getDefense() const {
            return this->defense;
        }

        std::string getFaction() const {
            return this->faction;
        }
 
        // These are setters 
        void setCurrent_Pos(const int &newCurrent_Pos) {
            this->current_pos = newCurrent_Pos;
        }

        void setName(const std::string &newName) {
            this->name = newName;
        }
 
        void setAttack(const int &newAttack) {
            this->attack = newAttack;
        }
 
        void setDefense(const int &newDefense) {
            this->defense = newDefense;
        }

        void setFaction(const std::string &newFaction) {
            this->faction = newFaction;
        }

    private: // THIS MEANS user cannot modify 
        int current_pos;
        std::string name;
        int attack;
        int defense;
        std::string faction;

};

void print_hangars(const std::vector<Ship>& hangar){ //YEA I REALIZED THAT I DIDNT NEED TO KEEP DOING << FOR COLORS THEN TO NEXT IT CAN TECHNICALLY ALL BE DONE  IN ONE LINE WOUDL HAVE BEEN NICE LEARNT THAT ON THE LAST COLOR GREAT IF STRING BUT FOR .GET NAME CANT 
    for (int i = 0; i < hangar.size(); i++) {
        std::cout << i+1 << ')' << " Name of ship: " << "\033[35m" << hangar[i].getName() << "\033[0m" << '\n';
        std::cout << '\t' << '\t' << "-Attack Power:  " << "\033[31m" << hangar[i].getAttack() << "\033[0m" <<'\n';
        std::cout << '\t' << '\t' << "-Defense Power: " << "\033[34m" << hangar[i].getDefense() << "\033[0m"<< '\n';
        std::cout << '\t' << '\t' << "-Faction:       " << hangar[i].getFaction() << '\n';
        std::cout << '\n';
    }
    std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";
}

void Pick_Ships (std::vector<Ship>& hangar, std::map<int, Ship>& ShipDataBase, int max){// NOT const for the hangar since we are modifyign it rest not 
    int counter = 0;
    int ship_count = 3;
    
    while (counter < max){
        std::cout << "You have this many more Ships you can select from: " << ship_count << ", Pick your ships Captain, please tell me the number you want the correspond to the ships you just looked at: ";
            int choices;
            std::cin >> choices;

            while (!ShipDataBase.count(choices)) {  // keeps looping if invalid
                std::cout << "Invalid, pick 1-6: ";
                std::cin >> choices;
            }
    //UPDATE TO NEWEST VERION OF CPP CASUE I CANT USE .CONTAINS WOUDL HAVE BEEN PERFECT CASUE IT LITEALLY CHECK THE HASH IF IT EXSIT OR COANTIS THAT VALUE 
            hangar.push_back(ShipDataBase[choices]);//Yo since my choice "LAAT" exitst --- add this to my vector (push.back) whjich was (my hangar)
            counter++;
            ship_count--;
            std::cout << '\n';
    }
    std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";
}


void Rand_Ships (std::vector<Ship>& hangar, std::map<int, Ship>& ShipDataBase, int max, std::mt19937& gen, std::uniform_int_distribution<int>&distrib){
    int new_counter = 0;
    while(new_counter < max){
        
        int rand_num = distrib(gen);                      // same job as rand() — generates the number

        if(ShipDataBase.count(rand_num)){
            hangar.push_back(ShipDataBase[rand_num]);//Yo since my choice "LAAT" exitst --- add this to my vector (push.back) whjich was (my hangar)
        }
        new_counter++;
    }
}

void damage_report (const Ship& attacker, const Ship& defender, int damage, int defense_before) {
    std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";
        std::cout << "DAMAGE REPORT:\n";
        std::cout << "\033[35m" << attacker.getName() << "\033[0m" << " attacked " << "\033[35m" << defender.getName() << "\033[0m"<< '\n';
        std::cout << "Damage Inflicted: " << "\033[31m" << damage << "\033[0m" << '\n';
        std::cout << "\033[35m" << defender.getName() << "\033[0m" << " defense: " << "\033[34m" << defense_before << "\033[0m" << " --> " << "\033[34m" << defender.getDefense() << "\033[0m" << '\n';

}

void destroyed_in_battle(std::vector<Ship>& hangar, int position){

    if (hangar[position].getDefense() <= 0) {
            std::cout << "\033[35m"  << hangar[position].getName() << "\033[0m" << " destroyed!\n";
            hangar.erase(hangar.begin() + (position));
        }

}



int main(){

/*//First phase of code to dynamically add turns out DUMBEST IDEA 
            //     std::vector <Ship> hangar; //says hey make a array which here its a vector --- this is where ill store ships
            //     //Ship s;
            // //User input  --- here we could then add a while that says hey do u want to add another ship or till you max out teh hanger at 4 ships whcih woudl ba n i ++ counter thuign 
            //     std::cout << "User give me a class type, ship name, speed adn power" << '\n';
            //         //std::string UserShip; //idea is show ship class tupe his toyotacamry my gunship
            //         std::string str1;//name of ship --- his toyota my LAAT
            //         int speed;
            //         int power;

            //         //std::cin >> UserShip;
            //         std::cin >> str1;
            //         std::cin >> speed;
            //         std::cin >> power;
                
            // //creatign all the ship stuff - puttign into class    
            //     Ship UserShip(str1, speed, power); //means creat one ship object using users values  
            //             UserShip.getName();
            //             UserShip.getHorsePower();
            //             UserShip.getTorque()
            // //Storage
            //     hangar.push_back(UserShip); //This says hey i nned you to have the vector store my ship object - adn the object are the details ( name spped power etc)

            // //Print out my hangar
            //     //hangar[0].();
            //     //std::cout << hangar[0] <<'\n';
            //     std::cout << "Name of ship: " << hangar[0].getName() << '\n';
            //     hangar[0].getHorsePower();
            //     hangar[0].getTorque();


// Phase 2 

//The process of making and storign the ships themselves --- VECTOR APPROACH  

    //Syn help: hey make a vecotr rather  --- than <int> its <data type> and classes are a data type --- varible name
    // std::vector<Ship> availableShips; // This is the "array" in which when i mention a[0] for ex it woudl get laat --- the way this section works is hey my book called available ship has these chapters calles ships 
                        
//         //Syntax undersanding: for the array --- add this element (push.back) --- via the class put in all this info essnally --- syn done this IS ALL OBJECTS  
//         availableShips.push_back(Ship(1, "LAAT", 200, 250, "Republic"));//Republic --- doing this in the event i want to split in terms of factions essnally 
//         availableShips.push_back(Ship(2, "ARC 170", 300, 150, "Republic"));
//         availableShips.push_back(Ship(3, "N1 Starfighter", 250, 180, "Republic"));

//         availableShips.push_back(Ship(4, "Vulture Droid", 350, 100, "Seperatist")); //Seperatist 
//         availableShips.push_back(Ship(5, "Droid Tri-Fighter", 150, 400, "Seperatist"));
//         availableShips.push_back(Ship(6, "Hyena Class Droid-bomber", 500, 600, "Seperatist"));

// //User input idea is to ask user for what they want (max of 3 for rn) and to store into a new vector called "Player_hangar" adn then print 

//     //std::cout << "Pilot Choose ur Ships" << '\n';

//     // for(const auto& i : availableShips){ //cant use this sicne im using mulitpel data types --- int adn strings
//     //         std::cout << i << '\n';
//     // }
// //PURE DISPLAY OF ALL THE SHIPS AND QUALITYS THEY POSSESE
//     for (int i = 0; i < availableShips.size(); i++){ // the .size says hey duanically jsut go by size of the array ie we got 6 elemts 
//         std::cout << availableShips[i].getCurrent_Pos() << ')' << " Name of ship: " << availableShips[i].getName() << '\n';
//         std::cout << '\t' << '\t' << "-Attack Power:  " << availableShips[i].getHorsePower() << '\n';
//         std::cout << '\t' << '\t' << "-Defense Power: " << availableShips[i].getTorque() << '\n';
//         std::cout << '\t' << '\t' << "-Faction Power: " << availableShips[i].getFaction() << '\n';
//         std::cout << '\n';
    //}



*/
//6/7 3PM update use Hash to store teh ships tehemsel s as a object located withing the value --- print out --- let user choose whcih they like adn want to keep sotre into vector --- display vecotr 
//USER PICKS THERE SHIPS AND ADDS TO A CUSTOM HANGER--- Approach: new vecotr>then jsut ask uyser to pick utilize a hash map to make efficit othewise for loop with yuckyt if logic 

//My Storage via vecotr (array)
    std::vector<Ship> My_Hangar;

//Hash map to make easier --- BEFORE WE RUN CODE RATHER THAN ME PUTTING IN LAAT DO ANTOHER OBJECT PARTS CALL IT CALL_VAL ADN DO 1,2, ETC OTHERWISE CHAGE INT TO STD:STRING
//HASH'S SOLE PURPOSE IS TO LOOK UP VIA KEY TAHTS IT 
    std::map<int, Ship> ShipDataBase; //So this shoudl input the number from designated ship (LAAT is 1 bc 1)) and then wodul go to the class its
    ShipDataBase[1] = Ship(1, "V Wing", 300, 100, "Republic"); // Dps -- High attak low def
    ShipDataBase[2] = Ship(2, "ARC 170", 150, 150, "Republic"); // med -- med 
    ShipDataBase[3] = Ship(3, "Y Wing", 100, 300, "Republic"); // Tank -- high def low attk

    ShipDataBase[4] = Ship(4, "Droid Tri-Fighter", 300, 100, "Seperatist");
    ShipDataBase[5] = Ship(5, "Vulture Droid", 150, 150, "Seperatist");
    ShipDataBase[6] = Ship(6, "Hyena Class Droid-bomber", 100, 300, "Seperatist");

//Reoloring in Terminal --- a;wyus "\033" for cahracters --- followed by [numbers color adn then before next line essnally use [0 to rest all mu changes 
//Trivia hwo to let say seperatist be one color and republic be another 
        std::cout << "Captain choose ur ships" << '\n';
    //HOW I WOULD PRINT OUT A HASH I GUES 
    for (const auto& pair : ShipDataBase) {
    std::cout << pair.first << " -> " << "\033[35m" << pair.second.getName() << "\033[0m"
                            << " | ATK: " << "\033[31m" << pair.second.getAttack() << "\033[0m"
                            << " | DEF: " << "\033[34m" << pair.second.getDefense() << "\033[0m"
                            << " | Faction: " << pair.second.getFaction()
                            << '\n'; // PARI FIRST IS TEH KEY ADN PAIR SECODN IS VALUE  
    }
    std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";
//-Defense Power: " << "\033[34" << hangar[i].getDefense() << "\033[0m"<< '\n';

//This is func call as well as the max ship count we pick 
    int max_ship_count = 3;
    Pick_Ships(My_Hangar, ShipDataBase, max_ship_count);
   /*int counter = 0;
    int ship_count = 3;
    
    while (counter < max_ship_count){
        std::cout << "You have this many more Ships you can select from: " << ship_count << " , Pick your ships captain, please tell me the number you want the correspond to the ships you just looked at: ";
            int choices;
            std::cin >> choices;
    //UPDATE TO NEWEST VERION OF CPP CASUE I CANT USE .CONTAINS WOUDL HAVE BEEN PERFECT CASUE IT LITEALLY CHECK THE HASH IF IT EXSIT OR COANTIS THAT VALUE 
    //.COUNT JUST RETURN 1 IF EXITS ELSE RETURN 0 SO NO REAL CHOICE 
        if(ShipDataBase.count(choices)){
            My_Hangar.push_back(ShipDataBase[choices]);//Yo since my choice "LAAT" exitst --- add this to my vector (push.back) whjich was (my hangar)
        }
        counter++;
        ship_count--;
    }*/ 

//Printing what USERS fleet/hangar is
    std::cout << "Captain your fleet: " << '\n'; 
    print_hangars(My_Hangar);
    /*  for (int i = 0; i < My_Hangar.size(); i++){ // the .size says hey duanically jsut go by size of the array ie we got 6 elemts 
        std::cout << My_Hangar[i].getCurrent_Pos() << ')' << " Name of ship: " << My_Hangar[i].getName() << '\n';
        std::cout << '\t' << '\t' << "-Attack Power:  " << My_Hangar[i].getHorsePower() << '\n';
        std::cout << '\t' << '\t' << "-Defense Power: " << My_Hangar[i].getTorque() << '\n';
        std::cout << '\t' << '\t' << "-Faction Power: " << My_Hangar[i].getFaction() << '\n';
        std::cout << '\n';
    }*/

/*Notes: Look into optimizaton --- use vecotrs as smallar containers of storage ie hangares vs HASH of whcih we store the whoel to have a better collectiy 
//ALSO WHNEW I PRUINT WITH TEH HASH STUFF NEED TO ESNALLY USE MAP NOT UNORDERED ITS KIDAN IN TEH ANEAM -- unordered is hash vs map is bst
//if i were to sort my ship picks via faction or ghihes to lower in a cateory ie attk use some sroptign abesf algo
//no idea why bst better for some reason gues its balanceing idk

//Enemy selection --- thinkign two option first is me sayign hey do you want to pick (switch case) or use a randomizer (rand)
*/
// apparently this is the old way to do it ie the c way 
// srand(time(0))
// int random_num = rand() % 6 + 1;

   


    std::vector<Ship> Enemy_Hangar;
    //all for new randomizer could use old way tho --- leave outside think this as setting eveerythign up 
    std::random_device rd;                            // same job as time(0) — gets a seed --- seed: gives a random starting point 
    std::mt19937 gen(rd());                           // same job as srand() — sets up the engine --- engine: generate from there  
    std::uniform_int_distribution<int> distrib(1,6);  // same job as % 6 — sets the range


    std::cout << "Captain do you want to have the enemy fleet randomized [1] or do you want to pick [2]: ";
        int enemy_fleet_pick;
        std::cin >> enemy_fleet_pick;
            //cond to make sure u pick 
            while (enemy_fleet_pick != 1 && enemy_fleet_pick != 2) {  // keeps looping if invalid
                std::cout << "Invalid, pick 1 or 2: ";
                std::cin >> enemy_fleet_pick;
            } 
    std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";
    switch (enemy_fleet_pick) {

        case (1):
            Rand_Ships(Enemy_Hangar, ShipDataBase, max_ship_count, gen, distrib);
            break;
        case (2):
            Pick_Ships(Enemy_Hangar, ShipDataBase, max_ship_count);
            break;

    }
    std::cout << "Captain the Enemy fleet appears to have: " << '\n';
    print_hangars(Enemy_Hangar);

    /*for (int i = 0; i < Enemy_Hangar.size(); i++){ // the .size says hey duanically jsut go by size of the array ie we got 6 elemts 
        std::cout << Enemy_Hangar[i].getCurrent_Pos() << ')' << " Name of ship: " << Enemy_Hangar[i].getName() << '\n';
        std::cout << '\t' << '\t' << "-Attack Power:  " << Enemy_Hangar[i].getHorsePower() << '\n';
        std::cout << '\t' << '\t' << "-Defense Power: " << Enemy_Hangar[i].getTorque() << '\n';
        std::cout << '\t' << '\t' << "-Faction Power: " << Enemy_Hangar[i].getFaction() << '\n';
        std::cout << '\n';
    }*/

//turn the display of vecotr hangars into fucntions 
//clen up so in termianl eveytgin is easier to look at ie player anems are colored maybe do liek a ========================= to split up large sextion 



//Actual turn based sorta idea of User goes first i pick a ship to attk then have the Enemy attack once --- idk seems kinda odd 
int turn = 1;
while(!My_Hangar.empty() && !Enemy_Hangar.empty()){ // Checking if the vectors are empty
   
    std::cout << "\033[33m" << "TURN " << turn << "\033[0m" << std::string(60, '-') << '\n';

//User Picks Ship to use --- print get value let that value -1 is ship then let that be variubel 
    std::cout << "My fleet: " << '\n';
    print_hangars(My_Hangar);
    std::cout << "Which ship do you want to use Captain (Pick number): ";
        int ship_select;
        std::cin >> ship_select; //display who we have chosen as well as expected outcomes of attacking a certain ship and dsipaly left over 
            while (ship_select < 1 || ship_select > (int)My_Hangar.size()) {  // keeps looping if invalid
                std::cout << "Invalid, pick a number that corresponds to one of the ships you got: ";
                std::cin >> ship_select;
            } 
    std::cout << ship_select << ')' << " Name of ship: " << "\033[35m" << My_Hangar[ship_select-1].getName() << "\033[0m" << '\n';
    std::cout << '\t' << '\t' << "-Attack Power:  " << "\033[31m" << My_Hangar[ship_select-1].getAttack() << "\033[0m" <<'\n';
    std::cout << '\t' << '\t' << "-Defense Power: " << "\033[34m" << My_Hangar[ship_select-1].getDefense() << "\033[0m" << '\n';
    std::cout << '\t' << '\t' << "-Faction:       " << My_Hangar[ship_select-1].getFaction() << '\n';
    std::cout << '\n';

//User picks which enemy ship to attack
    std::cout << "Enemy Fleet:" << '\n';
    print_hangars(Enemy_Hangar);
    std::cout << "Captain, who are we attacking!!!!! (Pick the number associtate to ship): ";
        int target;
        std::cin >> target;
            while (target < 1 || target > (int)Enemy_Hangar.size()) {  // keeps looping if invalid
                std::cout << "Invalid, pick a number that corresponds to one of the ships enemy has, Note that the ships did move essnally or get pushed down so just go by new numbers: ";
                std::cin >> target;
            } 
    
//if i said attack first thate located at elemtn 1 so target which i said 1 minus 1 so when i say attak the thrid ship vector says thats 2 to target minus 
    int defense_before_1 = Enemy_Hangar[target-1].getDefense(); // save first    
    Enemy_Hangar[target - 1].setDefense(Enemy_Hangar[target - 1].getDefense() - My_Hangar[ship_select - 1].getAttack());
        
    
    //DAMAGE REPORT OF WHAT JSUT HAPPENED --- this was the ship we used > damage done > what enemy has left 
    damage_report(My_Hangar[ship_select-1], Enemy_Hangar[target-1], My_Hangar[ship_select-1].getAttack(), defense_before_1);

//Ship hits 0 defense, remove it
    destroyed_in_battle(Enemy_Hangar, target-1); 
    
        // if (Enemy_Hangar[target - 1].getDefense() <= 0) {
        //     std::cout << Enemy_Hangar[target - 1].getName() << " destroyed!\n";
        //     Enemy_Hangar.erase(Enemy_Hangar.begin() + (target - 1));
        // }
  
    std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";



// Enemy attacks random player ship
    if(!Enemy_Hangar.empty()) { // Purpose of this loop si to check beofre enemy attack ig
        
        std::cout << "Captain, the enemy appears to be getting ready for an attack" << '\n';

        //Enemy behind the scenes --- need to do same idea of rand generate ship number to attack 
        int enemy_select = distrib(gen) % Enemy_Hangar.size();
//Enemy ship display
        std::cout << "Enemy is attacking with: " << "\033[35m" << Enemy_Hangar[enemy_select].getName() << "\033[0m" << '\n';

        std::cout << enemy_select+1 << ')' << " Name of ship: " << "\033[35m" << Enemy_Hangar[enemy_select].getName() << "\033[0m" << '\n';
        std::cout << '\t' << '\t' << "-Attack Power:  " << "\033[31m" << Enemy_Hangar[enemy_select].getAttack() << "\033[0m" <<'\n';
        std::cout << '\t' << '\t' << "-Defense Power: " << "\033[34m" << Enemy_Hangar[enemy_select].getDefense() << "\033[0m" <<'\n';
        std::cout << '\t' << '\t' << "-Faction:       " << Enemy_Hangar[enemy_select].getFaction() << '\n';
        std::cout << '\n';

        int rand_target = distrib(gen) % My_Hangar.size();
        int defense_before_2 = My_Hangar[rand_target].getDefense(); // save first    
        My_Hangar[rand_target].setDefense(My_Hangar[rand_target].getDefense() - Enemy_Hangar[enemy_select].getAttack());

        damage_report(Enemy_Hangar[enemy_select], My_Hangar[rand_target], Enemy_Hangar[enemy_select].getAttack(), defense_before_2);
        destroyed_in_battle(My_Hangar, rand_target); 
        std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";
        }
    turn++;
    }

    // Winner
    if (My_Hangar.empty()) {
        std::cout << "YOU LOST!?!?!?!? WHAT DID U FIGHT A SUPERIOR CLANKER LIKE GENERAL GREVIOUS THAT WANNA BE SITH LORD AND YOU LOST TO HIM WOW!!!!! WERE BOUT TO GET COMMANDER YULARN IN HERE TO WIN THIS BATTLE AGAINST THOSE CLANKERS\n";
    } 

    else {
        std::cout << "YOU WON!!!!!!ITS JUST LIKE THE SIMULATIONS\n"; //HAHA funny star wars reference
    }

return 0;
};
//chage text so its like a traingin simulation
/*Important logical issues:
-when prompting to pich ships if i pick 7 i am missing a ship need a while check DONE 
-maybe when abotu to attack i propmt user with possibel outcomes for attacking 
-if not desrttporyed shwo a upadtaed comabt log ie i did x damage they have x left --- DONE
do the color ie red for damage blue for defense --- done
turn traker --- done  
let factions be diff colors ie republic is cyan sepis is green woudl need to be a fucnton that says if republic else other color but wouidl need to change EVERY SINGE TIME TO A FUNCTION CALL RATHER THAN JSUT A SET OF NUMBER YUCK NOT HARD BUT ANNOYING */


/*
  DONE --- phase 2 --- create up to 6 ( i want this to go by quick no BG3 final battle stuff) differnt ships change the hp adn torqe to offense defense >>> of whcih user is promted to pick up to at least half (have each of them have a purpsose morre offese bad defense etc) --- print selction plyer hanger
  DONE --- phase 3 --- same ^^^ but call it enemy hangar 
  DONE --- phase 4 --- implement the offsne defense essenally a funciton to subtract adn if 0 say destroyed 
  NA DUMB --- pahse 5 --- implemtn a money absed ssystem of whcih you can win adn lose and get money thign the balckjack game 
  */