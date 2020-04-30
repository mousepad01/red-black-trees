#include <iostream>
using namespace std;

///----------------------------------------------------------------------CLASS NODE--------------------------------------------------------------------------------------

class Node{

    Node * parent;
    Node * lchild;
    Node * rchild;

    int value;

    int freq;

    bool color; ///1 -> black, 0 -> red

public:

    Node(int k, int fr, bool c);

    int get_value();

    int get_freq();

    bool get_color();

    Node * get_lchild();

    Node * get_rchild();

    Node * get_parent();

    Node * get_uncle();

    void set_freq(int fr);

    void set_value(int k);

    void set_color(bool c);

    void set_parent(Node * aux);

    void set_lchild(Node * aux);

    void set_rchild(Node * aux);
};

///--------------------------------------------------------------------METHODS CLASS NODE--------------------------------------------------------------------------------
Node::Node(int k, int fr = 1, bool c = 0){

    value = k;

    freq = fr;

    color = c;

    parent = NULL;
    lchild = NULL;
    rchild = NULL;
}

int Node::get_value(){

    return value;
}

int Node::get_freq(){

    return freq;
}

bool Node::get_color(){

    return color;
}

Node * Node::get_lchild(){

    return lchild;
}

Node * Node::get_rchild(){

    return rchild;
}

Node * Node::get_parent(){

    return parent;
}

Node * Node::get_uncle(){       ///RECOMANDAT : a se folosi doar ca apel imbricat in functia fix_tree

    Node * p = this -> get_parent();

    if(p -> parent -> lchild == p)
        return p -> parent -> rchild;
    else
        return p -> parent -> lchild;
}

void Node::set_freq(int fr){

    freq = fr;
}

void Node::set_value(int k){

    value = k;
}

void Node::set_color(bool c){

    color = c;
}

void Node::set_parent(Node * aux){

    parent = aux;
}

void Node::set_lchild(Node * aux){

    if(aux != NULL)
        aux -> parent = this;

    this -> lchild = aux;
}

void Node::set_rchild(Node * aux){

    if(aux != NULL)
        aux -> parent = this;

    this -> rchild = aux;
}

///---------------------------------------------------------------------------CLASS RBT-----------------------------------------------------------------------------------

class RBT{

    Node * root;

    ///toate metodele del_case_k apelate DOAR din interiorul metodei delete_val(int val);

    void del_case_1(Node * n);

    void del_case_2(Node * n);

    void del_case_3(Node * n);

    void del_case_4(Node * n);

    void del_case_5(Node * n);

    void del_case_6(Node * n);

public:

    RBT(int rval);

    void set_root(Node * x);

    void inorder_check(Node * current);

    void replace_node(Node * x, Node * ch);

    void left_rotate(Node * x);

    void right_rotate(Node * x);

    Node * get_root();

    Node * find_next(Node * aux);

    Node * find_prev(Node * aux);

    Node * find_min();

    Node * find_max();

    Node * find_value(int val);

    void delete_value(int val);     /// !!! functie de delete pt BTS normala ( nu satisface nici o proprietate a red black trees) !!!

    void delete_ok(int val);

    void delete_val(int val);

    void fix_tree(Node * x);

    void insert_node(Node * toin);
};

///--------------------------------------------------------------------------METHODS CLASS RBT----------------------------------------------------------------------------

RBT::RBT(int rval){ /// ok

    root = new Node(rval, 1, 1);

    root -> set_lchild(NULL);
    root -> set_rchild(NULL);
    root -> set_parent(NULL);
}

void RBT::set_root(Node * x){ ///ok

    root = x;
    root -> set_parent(NULL);
    root -> set_color(1);
}

void RBT::inorder_check(Node * current){ ///ok

    if(current == NULL){

        cout<<'\n';
        return;
    }

    Node *lc = current -> get_lchild();
    Node *rc = current -> get_rchild();

    if(lc != NULL)
        inorder_check(lc);

    cout<<current -> get_value()<<" : "<<current -> get_color()<<" | ";

    if(rc != NULL)
        inorder_check(rc);
}

void RBT::replace_node(Node * x, Node * ch){ ///ok

    if(x -> get_parent() == NULL){

        set_root(ch);
        return;
    }

    ch -> set_parent(x -> get_parent());

    if(x -> get_parent() -> get_lchild() == x)
        x -> get_parent() -> set_lchild(ch);
    else
        x -> get_parent() -> set_rchild(ch);
}

void RBT::left_rotate(Node * x){ ///ok

    Node * parent = x -> get_parent();
    ///Node * a = x -> get_lchild();
    Node * y = x -> get_rchild();

    if(y == NULL)
        return;

    Node * b = y -> get_lchild();
    Node * c = y -> get_rchild();

    if(parent != NULL){

        if(parent -> get_lchild() == x)
            parent -> set_lchild(y);
        else
            parent -> set_rchild(y);
    }
    else
        set_root(y);

    x -> set_rchild(b);
    y -> set_lchild(x);
}

void RBT::right_rotate(Node * x){ ///ok

    Node * parent = x -> get_parent();
    Node * y = x -> get_lchild();

    if(y == NULL)
        return;

    ///Node * a = y -> get_lchild();
    Node * b = y -> get_rchild();
    Node * c = x -> get_rchild();

    if(parent != NULL){

        if(parent -> get_lchild() == x)
            parent -> set_lchild(y);
        else
            parent -> set_rchild(y);
    }
    else
        set_root(y);

    y -> set_rchild(x);
    x -> set_lchild(b);
}

Node * RBT::get_root(){ ///ok

    return root;
}

Node * RBT::find_next(Node * x){ ///ok

    Node *aux = x;

    if(aux -> get_rchild() != NULL){

        aux = aux -> get_rchild();

        while(aux -> get_lchild() != NULL){

            aux = aux -> get_lchild();
        }
    }
    else{

        while((aux -> get_parent() != NULL) && (aux -> get_parent() -> get_lchild() != aux)){

            aux = aux -> get_parent();
        }
        if(aux -> get_parent() != NULL)
            aux = aux -> get_parent();
    }

    if(aux -> get_value() <= x -> get_value())
        return x;

    return aux;
}

Node * RBT::find_prev(Node * x){ ///ok

    Node *aux = x;

    if(aux -> get_lchild() != NULL){

        aux = aux -> get_lchild();

        while(aux -> get_rchild() != NULL){

            aux = aux -> get_rchild();
        }
    }
    else{

        while((aux -> get_parent() != NULL) && (aux -> get_parent() -> get_rchild() != aux)){

            aux = aux -> get_parent();
        }
        if(aux -> get_parent() != NULL)
            aux = aux -> get_parent();
    }

    if(aux -> get_value() <= x -> get_value())
        return x;

    return aux;
}

Node * RBT::find_min(){ ///ok

    Node * aux = root;

    while(aux -> get_lchild() != NULL)
        aux = aux -> get_lchild();

    return aux;
}

Node * RBT::find_max(){ ///ok

    Node * aux = root;

    while(aux -> get_rchild() != NULL)
        aux = aux -> get_rchild();

    return aux;
}

Node * RBT::find_value(int val){ ///ok

    Node * aux = root;

    while(aux != NULL){

        if(val < aux -> get_value()){

            aux = aux -> get_lchild();
        }
        else if(val > aux -> get_value()){

            aux = aux -> get_rchild();
        }
        else{

            return aux;
        }
    }

    return NULL;
}

void RBT::delete_value(int val){ ///ok     !!! delete pentru un BST normal !!!

    Node * todel = find_value(val);
    Node * parent = todel -> get_parent();

    Node *lc = todel -> get_lchild();
    Node *rc = todel -> get_rchild();

    if(lc == NULL && rc == NULL){

        if(parent == NULL){

            root = NULL;
            return;
        }

        if(parent -> get_lchild() == todel)
            parent -> set_lchild(NULL);
        else
            parent -> set_rchild(NULL);
    }
    else if(lc == NULL){

        if(parent == NULL){

            root = rc;
            return;
        }

        if(parent -> get_lchild() == todel)
            parent -> set_lchild(rc);
        else
            parent -> set_rchild(rc);

        rc -> set_parent(parent);
    }
    else if(rc == NULL){

        if(parent == NULL){

            root = lc;
            return;
        }

        if(parent -> get_lchild() == todel)
            parent -> set_lchild(lc);
        else
            parent -> set_rchild(lc);

        lc -> set_parent(parent);
    }
    else{

        Node * nextval = find_next(todel);

        int changeval = nextval -> get_value();

        delete_value(changeval);
        todel -> set_value(changeval);
    }
}

void RBT::del_case_6(Node * n){

    Node * s;

    if(n -> get_parent() -> get_lchild() == n)
        s = n -> get_parent() -> get_rchild();
    else
        s = n -> get_parent() -> get_lchild();

    s -> set_color(n -> get_parent() -> get_color());

    n -> get_parent() -> set_color(1);

    if(n -> get_parent() -> get_lchild() == n){

        if(s -> get_rchild() != NULL)
            s -> get_rchild() -> set_color(1);

        left_rotate(n -> get_parent());
    }
    else{

        if(s -> get_lchild() != NULL)
            s -> get_lchild() -> set_color(1);

        right_rotate(n -> get_parent());
    }
}

void RBT::del_case_5(Node * n){

    Node * s;

    if(n -> get_parent() -> get_lchild() == n)
        s = n -> get_parent() -> get_rchild();
    else
        s = n -> get_parent() -> get_lchild();

    if(s -> get_color() == 1){

        if(n -> get_parent() -> get_lchild() == n && s -> get_lchild() -> get_color() == 0 && s -> get_rchild() -> get_color() == 1){

            s -> set_color(0);

            if(s -> get_lchild() != NULL)
                s -> get_lchild() -> set_color(1);

            right_rotate(s);
        }
        else if(n -> get_parent() -> get_rchild() == n && s -> get_rchild() -> get_color() == 0 && s -> get_lchild() -> get_color() == 1){

            s -> set_color(0);

            if(s -> get_rchild() != NULL)
                s -> get_rchild() -> set_color(1);

            left_rotate(s);
        }
    }
    del_case_6(n);
}

void RBT::del_case_4(Node * n){

    Node * s;

    if(n -> get_parent() -> get_lchild() == n)
        s = n -> get_parent() -> get_rchild();
    else
        s = n -> get_parent() -> get_lchild();

    if(n -> get_parent() -> get_color() == 0 && s -> get_color() == 1 && (s -> get_lchild() == NULL || s -> get_lchild() -> get_color() == 1) && (s -> get_rchild() == NULL || s -> get_rchild() -> get_color() == 1)){

        s -> set_color(0);
        n -> get_parent() -> set_color(1);
    }
    else{

        del_case_5(n);
    }
}

void RBT::del_case_3(Node * n){

    Node * s;

    if(n -> get_parent() -> get_lchild() == n)
        s = n -> get_parent() -> get_rchild();
    else
        s = n -> get_parent() -> get_lchild();

    if(n -> get_parent() -> get_color() == 1 && s -> get_color() == 1 && (s -> get_lchild() == NULL || s -> get_lchild() -> get_color() == 1) && (s -> get_rchild() == NULL || s -> get_rchild() -> get_color() == 1)){

        s -> set_color(0);
        del_case_1(s -> get_parent());
    }
    else{

        del_case_4(n);
    }
}

void RBT::del_case_2(Node * n){

    Node * s;

    if(n -> get_parent() -> get_lchild() == n)
        s = n -> get_parent() -> get_rchild();
    else
        s = n -> get_parent() -> get_lchild();


    if(s -> get_color() == 0){

        n -> get_parent() -> set_color(0);
        s -> set_color(1);

        if(n -> get_parent() -> get_lchild() == n)
            left_rotate(n -> get_parent());
        else
            right_rotate(n -> get_parent());
    }
    del_case_3(n);
}

void RBT::del_case_1(Node * n){

    ///trec mai departe doar daca nu e radacina; asigurarea transformarii sale in radacina dupa caz, in interiorul functiei delete_val -> replace_node -> set_root

    if(n -> get_parent() != NULL)
        del_case_2(n);
}

void RBT::delete_val(int val){

    Node * todel = find_value(val);
    Node * parent = todel -> get_parent();

    Node * lc = todel -> get_lchild();
    Node * rc = todel -> get_rchild();

    ///tratare caz cand nodul de sters are 2 copii nenuli

    if(lc != NULL && rc != NULL){

        Node * nextval = find_next(todel);

        int changeval = nextval -> get_value();

        delete_val(changeval);
        todel -> set_value(changeval);

        return;
    }

    ///tratarea cazurilor cand nodul de sters are cel mult un copil nenul

    ///selectarea copilului nodului de eliminat

    Node * x;

    if(rc != NULL)
        x = rc;
    else
        x = lc;

    bool x_is_null = false;

    if(x == NULL){  ///simulez un nod cu valoarea NULL, dar care EXISTA ca obiect

        x = new Node(666, 1, 1); /// RANDOM VALUE, culoarea OBLIGATORIU NEGRU

        x_is_null = true;

        x -> set_parent(todel);
        x -> set_lchild(NULL);
        x -> set_rchild(NULL);

        todel -> set_lchild(x); /// se putea alege ca nodul simulat null sa fie fiul drept, nu conteaza
    }

    replace_node(todel, x);     ///din acest moment, todel este scos din arbore si inlocuit cu fiul sau (real sau null simulat)

    if(todel -> get_color() == 1){

        if(x -> get_color() == 0){

            x -> set_color(1);
        }
        else{

            del_case_1(x);
        }
    }

    if(x == root && x_is_null){

        root = NULL;
    }
    else if(x_is_null){

        if(x -> get_parent() -> get_lchild() == x)
            x -> get_parent() -> set_lchild(NULL);
        else
            x -> get_parent() -> set_rchild(NULL);
    }
}

void RBT::fix_tree(Node * x){ ///ok

    Node * parent = x -> get_parent();

    if(parent == NULL){                                 /// caz 1: nodul este radacina

        x -> set_color(1);
    }
    else if(parent -> get_color() == 1){                ///caz 2: nodul introdus este introdus deja cum trebuie ( tatal este negru)

        return;
    }
    else{

        Node * u = x -> get_uncle();  /// daca tatal nu este negru, el va avea garantat un bunic (negru) deci apelul este valid
        Node * gp = parent -> get_parent();

        if(u != NULL && u -> get_color() == 0){         ///caz 3: tatal este rosu, iar unchiul este tot rosu -> cobor culoarea, apelez fix_tree pt bunic

            parent -> set_color(1);
            u -> set_color(1);
            gp -> set_color(0);

            fix_tree(parent -> get_parent());
        }
        else{                                           ///caz 4: tatal este rosu, unchiul este negru; -> rotatii si recolorare in functie de caz

            if(parent == gp -> get_lchild() && x == parent -> get_rchild()){

                left_rotate(parent);
                x = x -> get_lchild();      ///pregatire pas urmator
            }
            else if(parent == gp -> get_rchild() && x == parent -> get_lchild()){

                right_rotate(parent);
                x = x -> get_rchild();      ///pregatire pas urmator
            }

            parent = x -> get_parent();     ///reinitalizare pentru cazul cand intra in if/else de mai sus

            if(x == parent -> get_lchild()){

                right_rotate(gp);
            }
            else
                left_rotate(gp);

            parent -> set_color(1);
            gp -> set_color(0);
        }
    }
}

void RBT::insert_node(Node * toin){ ///ok

    if(root == NULL){

        set_root(toin);
        fix_tree(root);
    }

    Node * aux = root;
    Node * parent_aux;

    bool side; /// 0 left, 1 right

    int toinval = toin -> get_value();

    while(aux != NULL){

        if(toinval < aux -> get_value()){

            parent_aux = aux;
            aux = aux -> get_lchild();

            side = 0;
        }
        else if(toinval > aux -> get_value()){

            parent_aux = aux;
            aux = aux -> get_rchild();

            side = 1;
        }
        else{

            aux -> set_freq((aux -> get_freq()) + 1);
            return;
        }
    }

    if(side == 0)
        parent_aux -> set_lchild(toin);
    else
        parent_aux -> set_rchild(toin);

    toin -> set_parent(parent_aux);

    fix_tree(toin);
}


int main(){

    RBT tree(60);

    ///cout<<tree.get_root() -> get_color()<<'\n'<<'\n'<<'\n';

    ///cout<<tree.get_root() -> get_value();

    ///tree.delete_value(tree.get_root() -> get_value());

    Node * aux = new Node(60);
    tree.insert_node(aux);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    Node * aux2 = new Node(110);
    tree.insert_node(aux2);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    Node * aux3 = new Node(50);
    tree.insert_node(aux3);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    Node * aux4 = new Node(750);
    tree.insert_node(aux4);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    Node * aux5 = new Node(20);
    tree.insert_node(aux5);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    Node * aux6 = new Node(10);
    tree.insert_node(aux6);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    Node * aux7 = new Node(230);
    tree.insert_node(aux7);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    Node * aux8 = new Node(55);
    tree.insert_node(aux8);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    Node * aux9 = new Node(52);
    tree.insert_node(aux9);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    Node * aux10 = new Node(57);
    tree.insert_node(aux10);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    tree.delete_val(230);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    tree.delete_val(10);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    tree.delete_val(52);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    tree.delete_val(110);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    tree.delete_val(50);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    tree.delete_val(55);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    tree.delete_val(60);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    tree.delete_val(57);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    tree.delete_val(20);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    tree.delete_val(750);
    tree.inorder_check(tree.get_root());
    cout<<'\n'<<'\n';

    return 0;
}
