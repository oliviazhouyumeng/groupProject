#include "block.h"
#include "tblock.h"

using namespace std;


TBlock::TBlock(Grid &g): Block{3, 0, level, "A", false}{
    auto a = make_shared<Cell>(&g.getCell(2, 0));
    cells.push_back(a);
    auto b = make_shared<Cell>(&g.getCell(2, 1));
    cells.push_back(b);
    auto c = make_shared<Cell>(&g.getCell(2, 2));
    cells.push_back(c);
    auto d = make_shared<Cell>(&g.getCell(3, 1));
    cells.push_back(d);
}
    

//size_t x, y;
//int level;
//std::string type; // type: "A"(default), "B", "C", "D" clockwise:A->B->C->D
//bool heavy; // default: false
//std::vector<std::shared_ptr<Cell>> cells; // a Block originally contains four Cell

void TBlock::left(Grid &g){///////////not done
    
}



void TBlock::right(Grid &g){
    if (type == "A") {
        auto ur = make_shared<Cell>(cells.at(2)); //upper right cell
        size_t ur_x = ur->getInfo().row;
        size_t ur_y = ur->getInfo().col;
        Cell &new_ur_ref = g.getCell(ur_x, ur_y+1);
        Cell &new_lm_ref = g.getCell(ur_x+1, ur_y); // lower middle cell
        if(new_ur_ref.getInfo().colour == Colour::White && new_lm_ref.getInfo().colour == Colour::White){//both new ur and new lm are empty
            auto old_ul = make_shared<Cell>(cells.at(0)); // old upper left
            auto old_lm = make_shared<Cell>(cells.at(3)); // old lower middle
            new_ur_ref.setColour(Colour::Orange, g);
            new_ur_ref.setColour(Colour::Orange, g);
            old_ul->setColour(Colour::White, g);
            old_ul->setColour(Colour::White, g);
            
            cells.erase(cells.begin()); // old first element(upper left)
            cells.erase(cells.begin()+2); // old forth element(lower middle)
            auto new_ur = make_shared<Cell>(&g.getCell(ur_x, ur_y+1));
            auto new_lm = make_shared<Cell>(&g.getCell(ur_x+1, ur_y));
            cells.push_back(new_ur);
            cells.push_back(new_lm);
            old_ul->notifyObservers();
            old_lm->notifyObservers();
            new_ur->notifyObservers();
            new_lm->notifyObservers();
        }
    }
    if (type == "B") {
        auto mr = make_shared<Cell>(cells.at(1)); //middle right cell
        size_t mr_x = mr->getInfo().row;
        size_t mr_y = mr->getInfo().col;
        Cell &new_ur_ref = g.getCell(mr_x-2, mr_y+2);
        Cell &new_mr_ref = g.getCell(mr_x-1, mr_y+2);
        Cell &new_lr_ref = g.getCell(mr_x, mr_y+2);
        if(new_ur_ref.getInfo().colour == Colour::White && new_mr_ref.getInfo().colour == Colour::White && new_lr_ref.getInfo().colour == Colour::White){
            auto old_ml = make_shared<Cell>(cells.at(3)); // old middle left
            auto old_ur = make_shared<Cell>(cells.at(0)); //old upper right
            auto old_lr = make_shared<Cell>(cells.at(2)); // old lower left
            new_ur_ref.setColour(Colour::Orange, g);
            new_mr_ref.setColour(Colour::Orange, g);
            new_lr_ref.setColour(Colour::Orange, g);
            old_ml->setColour(Colour::White, g);
            old_ur->setColour(Colour::White, g);
            old_lr->setColour(Colour::White, g);
            
            cells.erase(cells.begin()); // old first(upper right)
            cells.erase(cells.begin()+1); // old third(lower right)
            cells.erase(cells.begin()+1); // old forth(middle right)
            
            auto new_ur = make_shared<Cell>(&g.getCell(mr_x-2, mr_y+2));
            auto new_mr = make_shared<Cell>(&g.getCell(mr_x-1, mr_y+2));
            auto new_lr = make_shared<Cell>(&g.getCell(mr_x, mr_y+2));
            cells.insert(cells.begin(), new_ur);
            cells.insert(cells.begin()+1, new_mr);
            cells.insert(cells.begin()+2, new_lr);
            old_ur->notifyObservers();
            old_ml->notifyObservers();
            old_lr->notifyObservers();
            new_ur->notifyObservers();
            new_mr->notifyObservers();
            new_lr->notifyObservers();
        }
        
    }
    if (type == "C") {
        auto lr = make_shared<Cell>(cells.at(0)); // lower right cell
        size_t lr_x = lr->getInfo().row;
        size_t lr_y = lr->getInfo().col;
        Cell &new_um_ref = g.getCell(lr_x-1, lr_y); // upper middle
        Cell &new_lr_ref = g.getCell(lr_x, lr_y+1); //lower right
        if(new_um_ref.getInfo().colour == Colour::White && new_lr_ref.getInfo().colour == Colour::White){
            auto old_ll = make_shared<Cell>(cells.at(2)); // old lower left
            auto old_um = make_shared<Cell>(cells.at(3)); // old upper middle
            new_lr_ref.setColour(Colour::Orange, g);
            new_um_ref.setColour(Colour::Orange, g);
            old_ll->setColour(Colour::White, g);
            old_um->setColour(Colour::White, g);
            
            cells.erase(cells.begin()+3);
            cells.erase(cells.begin()+2);
            
            auto new_lr = make_shared<Cell>(&g.getCell(lr_x, lr_y+1));
            auto new_um = make_shared<Cell>(&g.getCell(lr_x-1, lr_y));
            cells.insert(cells.begin(), new_lr);
            cells.push_back(new_um);
            old_um->notifyObservers();
            old_ll->notifyObservers();
            new_um->notifyObservers();
            new_lr->notifyObservers();
        }
    }
    else{ // "D" type
        auto mr = make_shared<Cell>(cells.at(3)); //middle right
        size_t mr_x = mr->getInfo().row;
        size_t mr_y = mr->getInfo().col;
        Cell &new_ul_ref = g.getCell(mr_x-1, mr_y); // new upper left
        Cell &new_mr_ref = g.getCell(mr_x, mr_y+1); // new middle right
        Cell &new_ll_ref = g.getCell(mr_x+1, mr_y); // new lower left
        if(new_ul_ref.getInfo().colour == Colour::White && new_mr_ref.getInfo().colour == Colour::White && new_ll_ref.getInfo().colour == Colour::White){
            auto old_ul = make_shared<Cell>(cells.at(2)); //old upper left
            auto old_ml = make_shared<Cell>(cells.at(1)); // old middle left
            auto old_ll = make_shared<Cell>(cells.at(0)); //old lower left
            new_ul_ref.setColour(Colour::Orange, g);
            new_mr_ref.setColour(Colour::Orange, g);
            new_ll_ref.setColour(Colour::Orange, g);
            old_ul->setColour(Colour::White, g);
            old_ml->setColour(Colour::White, g);
            old_ll->setColour(Colour::White, g);
            
            cells.erase(cells.begin());
            cells.erase(cells.begin());
            cells.erase(cells.begin());
            
            auto new_ul = make_shared<Cell>(&g.getCell(mr_x-1, mr_y));
            auto new_mr = make_shared<Cell>(&g.getCell(mr_x, mr_y+1));
            auto new_ll = make_shared<Cell>(&g.getCell(mr_x+1, mr_y));
            cells.insert(cells.begin(), new_ll);
            cells.push_back(new_ul);
            cells.push_back(new_mr);
            old_ul->notifyObservers();
            old_ml->notifyObservers();
            old_ll->notifyObservers();
            new_ul->notifyObservers();
            new_mr->notifyObservers();
            new_ll->notifyObservers();
        }
    }
}



void TBlock::down(Grid &g){
    shared_ptr<Cell> origin(&g.getCell(x, y));
    origin->notifyObservers();
}


void TBlock::clockwise(Grid &g){
    shared_ptr<Cell> origin(&g.getCell(x, y));
    origin->notifyObservers();
}
void TBlock::counterclockwise(Grid &g){
    shared_ptr<Cell> origin(&g.getCell(x, y));
    origin->notifyObservers();
}


void TBlock::drop(Grid &g){
    for(int i = 0; i < 18; i++){ //for 21 rows
        down(g);
    }
}

























