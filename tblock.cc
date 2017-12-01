#include "block.hpp"
#include "tblock.hpp"

using namespace std;


TBlock::TBlock(Grid &g): Block{3, 0, level, "A", false}{
    auto a = make_shared<Cell>(&g.getCell(2, 0));
    State newS = {StateType::AC};
    a->setColour(Colour::Orange, g);
    a->setState(newS);
    cells.push_back(a);
    auto b = make_shared<Cell>(&g.getCell(2, 1));
    b->setColour(Colour::Orange, g);
    b->setState(newS);
    cells.push_back(b);
    auto c = make_shared<Cell>(&g.getCell(2, 2));
    c->setColour(Colour::Orange, g);
    c->setState(newS);
    cells.push_back(c);
    auto d = make_shared<Cell>(&g.getCell(3, 1));
    d->setColour(Colour::Orange, g);
    d->setState(newS);
    cells.push_back(d);
}
    

//size_t x, y;
//int level;
//std::string type; // type: "A"(default), "B", "C", "D" clockwise:A->B->C->D
//bool heavy; // default: false
//std::vector<std::shared_ptr<Cell>> cells; // a Block originally contains four Cell

void TBlock::left(Grid &g){///////////not done
    State old_S = State{StateType::NA};
    State new_S = State{StateType::AC};
    if (type == "A") {
        Cell &new_ul_ref = g.getCell(x-1, y-1);//upper left
        Cell &new_lm_ref = g.getCell(x, y); //lower middle
        if(new_ul_ref.getInfo().colour == Colour::White && new_lm_ref.getInfo().colour == Colour::White){
            auto old_ur = make_shared<Cell>(cells.at(2));
            auto old_lm = make_shared<Cell>(cells.at(3));
            new_ul_ref.setColour(Colour::Orange, g);
            new_lm_ref.setColour(Colour::Orange, g);
            old_ur->setColour(Colour::White, g);
            old_lm->setColour(Colour::White, g);
            
            cells.pop_back();
            cells.pop_back();
            auto new_ul = make_shared<Cell>(g.getCell(x-1, y-1));
            auto new_lm = make_shared<Cell>(g.getCell(x, y));
            cells.push_back(new_lm);
            cells.insert(cells.begin(), new_ul);
            old_ur->setState(old_S);
            old_lm->setState(old_S);
            new_ul->setState(new_S);
            new_lm->setState(new_S);
            old_ur->notifyObservers();
            old_lm->notifyObservers();
            new_ul->notifyObservers();
            new_lm->notifyObservers();
            y--;
        }
    }
    else if (type == "B"){
        Cell &new_ur_ref = g.getCell(x-2, y);
        Cell &new_ml_ref = g.getCell(x-1, y-1);
        Cell &new_lr_ref = g.getCell(x, y);
        if(new_ur_ref.getInfo().colour == Colour::White && new_ml_ref.getInfo().colour == Colour::White && new_lr_ref.getInfo().colour == Colour::White){
            auto old_ur = make_shared<Cell>(cells.at(0));
            auto old_mr = make_shared<Cell>(cells.at(1));
            auto old_lr = make_shared<Cell>(cells.at(2));
            new_ur_ref.setColour(Colour::Orange, g);
            new_ml_ref.setColour(Colour::Orange, g);
            new_lr_ref.setColour(Colour::Orange, g);
            old_ur->setColour(Colour::White, g);
            old_mr->setColour(Colour::White, g);
            old_lr->setColour(Colour::White, g);
            
            cells.erase(cells.begin());
            cells.erase(cells.begin());
            cells.erase(cells.begin());
            auto new_ur = make_shared<Cell>(g.getCell(x-2, y));
            auto new_ml= make_shared<Cell>(g.getCell(x-1, y-1));
            auto new_lr = make_shared<Cell>(g.getCell(x, y));
            old_ur->setState(old_S);
            old_mr->setState(old_S);
            old_lr->setState(old_S);
            new_ur->setState(new_S);
            new_ml->setState(new_S);
            new_lr->setState(new_S);
            cells.insert(cells.begin(), new_ur);
            cells.push_back(new_lr);
            cells.push_back(new_ml);
            old_ur->notifyObservers();
            old_mr->notifyObservers();
            old_lr->notifyObservers();
            new_ur->notifyObservers();
            new_ml->notifyObservers();
            new_lr->notifyObservers();
            y--;
        }
    }
    else if(type == "C"){
        Cell &new_ll_ref = g.getCell(x, y-1);
        Cell &new_um_ref = g.getCell(x-1, y);
        if(new_ll_ref.getInfo().colour == Colour::White && new_um_ref.getInfo().colour == Colour::White){
            auto old_lr = make_shared<Cell>(cells.at(0));
            auto old_um = make_shared<Cell>(cells.at(3));
            new_ll_ref.setColour(Colour::Orange, g);
            new_um_ref.setColour(Colour::Orange, g);
            old_lr->setColour(Colour::White, g);
            old_um->setColour(Colour::White, g);
            
            cells.pop_back();
            cells.erase(cells.begin());
            auto new_ll = make_shared<Cell>(g.getCell(x, y-1));
            auto new_um = make_shared<Cell>(g.getCell(x-1, y));
            old_lr->setState(old_S);
            old_um->setState(old_S);
            new_ll->setState(new_S);
            new_um->setState(new_S);
            cells.push_back(new_ll);
            cells.push_back(new_um);
            old_lr->notifyObservers();
            old_um->notifyObservers();
            new_um->notifyObservers();
            new_ll->notifyObservers();
            y--;
        }
    }
    else { // type "D"
        Cell &new_ul_ref = g.getCell(x-2, y-1);
        Cell &new_ml_ref = g.getCell(x-1, y-1);
        Cell &new_ll_ref = g.getCell(x, y-1);
        if(new_ul_ref.getInfo().colour == Colour::White && new_ml_ref.getInfo().colour == Colour::White && new_ll_ref.getInfo().colour == Colour::White){
            auto old_ul = make_shared<Cell>(cells.at(2));
            auto old_mr = make_shared<Cell>(cells.at(3));
            auto old_ll = make_shared<Cell>(cells.at(0));
            new_ul_ref.setColour(Colour::Orange, g);
            new_ml_ref.setColour(Colour::Orange, g);
            new_ll_ref.setColour(Colour::Orange, g);
            old_ul->setColour(Colour::White, g);
            old_mr->setColour(Colour::White, g);
            old_ll->setColour(Colour::White, g);
            
            cells.pop_back();
            cells.pop_back();
            cells.erase(cells.begin());
            auto new_ul = make_shared<Cell>(g.getCell(x-2, y-1));
            auto new_ml = make_shared<Cell>(g.getCell(x-1, y-1));
            auto new_ll = make_shared<Cell>(g.getCell(x, y-1));
            old_ul->setState(old_S);
            old_mr->setState(old_S);
            old_ll->setState(old_S);
            new_ul->setState(new_S);
            new_ml->setState(new_S);
            new_ll->setState(new_S);
            cells.insert(cells.begin(), new_ul);
            cells.insert(cells.begin(), new_ml);
            cells.insert(cells.begin(), new_ll);
            old_ul->notifyObservers();
            old_ll->notifyObservers();
            old_mr->notifyObservers();
            new_ul->notifyObservers();
            new_ml->notifyObservers();
            new_ll->notifyObservers();
            y--;
        }
    }
}



void TBlock::right(Grid &g){
    State old_S = State{StateType::NA};
    State new_S = State{StateType::AC};
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
            old_ul->setState(old_S);
            old_lm->setState(old_S);
            new_ur->setState(new_S);
            new_lm->setState(new_S);
            cells.push_back(new_ur);
            cells.push_back(new_lm);
            old_ul->notifyObservers();
            old_lm->notifyObservers();
            new_ur->notifyObservers();
            new_lm->notifyObservers();
            y++;
        }
    }
    else if (type == "B") {
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
            old_ml->setState(old_S);
            old_ur->setState(old_S);
            old_lr->setState(old_S);
            new_ur->setState(new_S);
            new_mr->setState(new_S);
            new_lr->setState(new_S);
            cells.insert(cells.begin(), new_ur);
            cells.insert(cells.begin()+1, new_mr);
            cells.insert(cells.begin()+2, new_lr);
            old_ur->notifyObservers();
            old_ml->notifyObservers();
            old_lr->notifyObservers();
            new_ur->notifyObservers();
            new_mr->notifyObservers();
            new_lr->notifyObservers();
            y++;
        }
        
    }
    else if (type == "C") {
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
            old_ll->setState(old_S);
            old_um->setState(old_S);
            new_lr->setState(new_S);
            new_um->setState(new_S);
            cells.insert(cells.begin(), new_lr);
            cells.push_back(new_um);
            old_um->notifyObservers();
            old_ll->notifyObservers();
            new_um->notifyObservers();
            new_lr->notifyObservers();
            y++;
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
            old_ul->setState(old_S);
            old_ml->setState(old_S);
            old_ll->setState(old_S);
            new_ul->setState(new_S);
            new_mr->setState(new_S);
            new_ll->setState(new_S);
            cells.insert(cells.begin(), new_ll);
            cells.push_back(new_ul);
            cells.push_back(new_mr);
            old_ul->notifyObservers();
            old_ml->notifyObservers();
            old_ll->notifyObservers();
            new_ul->notifyObservers();
            new_mr->notifyObservers();
            new_ll->notifyObservers();
            y++;
        }
    }
}



void TBlock::down(Grid &g){
    auto old_ul = make_shared<Cell>(cells.at(0));
    auto old_um = make_shared<Cell>(cells.at(1));
    auto old_ur = make_shared<Cell>(cells.at(2));
    auto old_lm = make_shared<Cell>(cells.at(3));
    auto new_ul = make_shared<Cell>(&g.getCell(old_ul->getInfo().row + 1, old_ul->getInfo().col));
    auto new_um = make_shared<Cell>(&g.getCell(old_um->getInfo().row + 1, old_um->getInfo().col));
    auto new_ur = make_shared<Cell>(&g.getCell(old_ur->getInfo().row + 1, old_ur->getInfo().col));
    auto new_lm = make_shared<Cell>(&g.getCell(old_lm->getInfo().row + 1, old_lm->getInfo().col));
    if((new_ul->getInfo().colour == Colour::White || new_ul->getState().stype == StateType::AC) &&
       (new_um->getInfo().colour == Colour::White || new_um->getState().stype == StateType::AC) &&
       (new_ur->getInfo().colour == Colour::White || new_ur->getState().stype == StateType::AC) &&
       (new_lm->getInfo().colour == Colour::White || new_lm->getState().stype == StateType::AC)){
        old_ul->setColour(Colour::White, g);
        old_um->setColour(Colour::White, g);
        old_ur->setColour(Colour::White, g);
        old_lm->setColour(Colour::White, g);
        State old_S = State{StateType::NA};
        old_ul->setState(old_S);
        old_um->setState(old_S);
        old_ur->setState(old_S);
        old_lm->setState(old_S);
        new_ul->setColour(Colour::Orange, g);
        new_um->setColour(Colour::Orange, g);
        new_ur->setColour(Colour::Orange, g);
        new_lm->setColour(Colour::Orange, g);
        State new_S = State{StateType::AC};
        new_ul->setState(new_S);
        new_um->setState(new_S);
        new_ur->setState(new_S);
        new_lm->setState(new_S);
        cells.clear();
        cells.push_back(new_ul);
        cells.push_back(new_um);
        cells.push_back(new_ur);
        cells.push_back(new_lm);
        old_ul->notifyObservers();
        old_um->notifyObservers();
        old_ur->notifyObservers();
        old_lm->notifyObservers();
        new_ul->notifyObservers();
        new_um->notifyObservers();
        new_ur->notifyObservers();
        new_lm->notifyObservers();
        x++;
    }
}


void TBlock::clockwise(Grid &g){
    State old_S = State{StateType::NA};
    State new_S = State{StateType::AC};
    
    auto new_first = make_shared<Cell>(&g.getCell(x-2, y+1));
    if(new_first->getInfo().colour == Colour::White){
        
        auto old_first = make_shared<Cell>(cells.at(0));
        auto old_second = make_shared<Cell>(cells.at(1));
        auto old_third = make_shared<Cell>(cells.at(2));
        auto old_forth = make_shared<Cell>(cells.at(3));
        old_third->setColour(Colour::White, g);
        old_third->setState(old_S);
        auto new_second = make_shared<Cell>(old_second);
        auto new_third = make_shared<Cell>(old_forth);
        auto new_forth = make_shared<Cell>(old_first);
        cells.clear();
        new_first->setColour(Colour::Orange, g);
        new_first->setState(new_S);
        cells.push_back(new_first);
        cells.push_back(new_second);
        cells.push_back(new_third);
        cells.push_back(new_forth);
        old_third->notifyObservers();
        new_first->notifyObservers();
        this->cwtype();
    }
}

void TBlock::counterclockwise(Grid &g){
    State old_S = State{StateType::NA};
    State new_S = State{StateType::AC};
    auto new_third = make_shared<Cell>(&g.getCell(x-2, y+1));
    if(new_third->getInfo().colour == Colour::White) {
        auto old_first = make_shared<Cell>(cells.at(0));
        auto old_second = make_shared<Cell>(cells.at(1));
        auto old_third = make_shared<Cell>(cells.at(2));
        auto old_forth = make_shared<Cell>(cells.at(3));
        old_first->setColour(Colour::White, g);
        old_first->setState(old_S);
        auto new_first = make_shared<Cell>(old_forth);
        auto new_second = make_shared<Cell>(old_second);
        auto new_forth = make_shared<Cell>(old_third);
        cells.clear();
        new_third->setColour(Colour::Orange, g);
        new_third->setState(new_S);
        cells.push_back(new_first);
        cells.push_back(new_second);
        cells.push_back(new_third);
        cells.push_back(new_forth);
        old_first->notifyObservers();
        new_third->notifyObservers();
        this->ccwtype();
    }
    
}


void TBlock::drop(Grid &g){
    for(int i = 0; i < 18; i++){ //for 21 rows
        down(g);
    }
    State old_S = State{StateType::NA};
    auto first = make_shared<Cell>(cells.at(0));
    auto second = make_shared<Cell>(cells.at(1));
    auto third = make_shared<Cell>(cells.at(2));
    auto forth = make_shared<Cell>(cells.at(3));
    first->setState(old_S);
    second->setState(old_S);
    third->setState(old_S);
    forth->setState(old_S);
    first->notifyObservers();
    second->notifyObservers();
    third->notifyObservers();
    forth->notifyObservers();
}

























