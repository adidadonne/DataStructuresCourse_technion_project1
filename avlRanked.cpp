

#include "avlRanked.h"
// avlRanked constructor
//template<class T, class S>
avlRanked::avlRanked(): root_(nullptr), size_(0) , minNode_(nullptr) {}


//template<class T, class S>
avlRanked::~avlRanked() {
    minNode_ = nullptr;
    if( root_ != nullptr ){
        deleteTree(root_);
    }
}

//Post order deletion of a given node.
//template<class T, class S>////Added removeArtistMethod as bool to change the pointers inside the list of the songs while deleting the song from the tree
void avlRanked::deleteTree( avlRankedNode *node )  {
    if(node != nullptr) {
        deleteTree(node->left_);
        deleteTree(node->right_);

        delete node;
    }
}

//template<class T, class S>
avlRankedNode *avlRanked::getRoot()  {
    return root_;
}



//template<class T, class S>
avlRankedNode *avlRanked::findNode(avlRankedNode *root, int key)  {
    if( !root ) { return nullptr; }
    if( (root->key) == key ){
        return root;
    }
    else if ((root->key) > key) {
        return findNode( root->left_, key);
    }
    else{
        return findNode( root->right_, key);
    }

}

//template<class T, class S>
void avlRanked::insertNode(ImageTreeData* data, int key) {

    if ( (findNode(this->root_, key)) ) {
        throw IDAlreadyExists();
    }

    avlRankedNode * newNode = new avlRankedNode(data,key);

    if( !newNode ){
        throw allocationError(); // Couldn't create new node.
    }

    if( !root_ ){   // In case we have an empty tree.
        root_ = newNode;
        minNode_ = newNode;
    }

    else {
        root_ = insertNodeAux(root_, newNode, key);
    }
    size_++;
}


///
/// \tparam T
/// \param root the node you are currently at.
/// \param newNode the new node you want to insert.
/// \param key the new key for the newNode you want to insert.
/// \return avlRankedNode<T,S>* for th node you called the function.
//template<class T, class S>
avlRankedNode *avlRanked::insertNodeAux( avlRankedNode* root,  avlRankedNode* newNode, int key)  {

    // Inserting node the same way as we would on a binary search tree.
    if( (root->key) > key ) {
        if( root->left_ ) { // If we have left child, we keep searching.
            insertNodeAux(root->left_, newNode, key);
        }
        else {
            root->left_ = newNode;
            newNode->parent_ = root;
            if ( (minNode_->key) > key ) { minNode_ = newNode; }
        }
    }
    else {
        if( root->right_ ) { // If we have right child, we keep searching.
            insertNodeAux(root->right_, newNode, key);
        }
        else {
            root->right_ = newNode;
            newNode->parent_ = root;
        }
    }

    root->height = findHeight(root);

    // Updating rank
    root->w += 1;
//    if(root->left_){
//        root->w += root->left_->w;
//    }
//    if(root->right_){
//        root->w += root->right_->w;
//    }

    // Checking balance factor
    int rootBalance = findBalance(root);
    int leftBalance = findBalance(root->left_);
    int rightBalance = findBalance(root->right_);

    // Dealing with rotations in case we mess up our BF

    // Left left case:
    if (rootBalance > 1 && leftBalance >= 0) {
        return rightRotation(root);
    }

        // Left right case:
    else if (rootBalance > 1 && leftBalance == -1){
        root->left_= leftRotation(root->left_);
        return rightRotation(root);
    }

        // Right right case:
    else if (rootBalance < -1 && rightBalance <= 0){
        return leftRotation(root);
    }

        // Right left case:
    else if (rootBalance < -1 && rightBalance == 1) {
        root->right_= rightRotation(root->right_);
        return leftRotation(root);
    }

    // we return the (unchanged) avlRankedNode ptr.
    return root;

}

//template<class T, class S>
avlRankedNode *avlRanked::removeNode(avlRankedNode *root, int key) {
    //removing the node the same way as we would on a binary search tree.
    if( root == nullptr ){
        return root;
    }
    else if(key < (root->key)){
        root->left_= removeNode(root->left_,key);
    }
    else if(key > (root->key)){
        root->right_ = removeNode(root->right_,key);
    }
    else{ // we found the node to remove
        //case 1: leaf
        if(root->left_ == nullptr && root->right_ == nullptr) {

            if( root == minNode_ ){ //the only node without a parent
                if ( root != root_ ){ //in case we're removing the minNode
                    minNode_ = root->parent_;
                }
                else{
                    minNode_ = nullptr;
                    root_ = nullptr;
                }
            }
            delete root;
            root = nullptr;
            return root;

        }
            //case 2: 1 child
            //in this case we know that the child is a leaf because its an avlRanked tree
            //so we can copy and delete the child
        else if(root->left_ == nullptr) {

            if (root == root_){
                root_ = root->right_;
                minNode_=root->right_;
            }
            avlRankedNode *temp = root;
            root = root->right_;
            root->parent_= temp->parent_;
            if( temp == minNode_ ) {
                minNode_ = root;
            }
            delete temp;

        }
        else if(root->right_ == nullptr) {

            if (root == root_){
                root_ = root->left_;
            }

            avlRankedNode *temp = root;
            root->left_->parent_ = root->parent_;
            root = root->left_;
            delete temp;
        }
            //case 3: 2 child
        else{

            avlRankedNode *temp1 = findMax(root->left_);
            avlRankedNode *temp2 = root;

            swap(temp2,temp1);

            root = temp1;
            root->w = temp2->w;
            if (root_->parent_){
                root_ = root;
            }
            root->left_= removeNode(root->left_, temp2->key);
        }
    }
    // Updating the size
    size_--;

    // Updating the new height after deletion.
    root->height = findHeight(root);

    // Updating rank
    root->w = ((root->left_) ? root->left_->w : 0) + ((root->right_) ? root->right_->w : 0) + 1;

    // Checking balance factor
    int rootBalance = findBalance(root);
    int leftBalance = findBalance(root->left_);
    int rightBalance = findBalance(root->right_);

    // Dealing with rotations in case we mess up our BF

    // Left left case:
    if (rootBalance > 1 && leftBalance >= 0) {
        root = rightRotation(root);
    }
        // Left right case:
    else if (rootBalance > 1 && leftBalance == -1){
        root->left_= leftRotation(root->left_);
        root = rightRotation(root);
    }

        // Right right case:
    else if (rootBalance < -1 && rightBalance <= 0){
        root = leftRotation(root);
    }

        // Right left case:
    else if (rootBalance < -1 && rightBalance == 1) {
        root->right_= rightRotation(root->right_);
        root = leftRotation(root);
    }

    if (root_->parent_){
        root_ = root;
    }

    return root;
}


//template<class T, class S>
avlRankedNode *avlRanked::findMax(avlRankedNode *root) {
    while(root->right_){
        root = root->right_;
    }
    return root;
}


//Checking if we can access to the height parameter.
//template<class T, class S>
int avlRanked::checkHeight( avlRankedNode *root)  {
    if (nullptr == root) { return -1; }
    return root->height;
}
///
/// \tparam T
/// \param root the node we want to calculate the height for.
/// \return the node's height calculation.
//template<class T, class S>
int avlRanked::findHeight( avlRankedNode *root)  {
    int hl, hr = 0; //TODO: If something not working. check this one.
    hr = checkHeight(root->right_);
    hl = checkHeight(root->left_);

    return 1 + ( hl > hr ? hl : hr);
}

//template<class T, class S>
int avlRanked::findBalance( avlRankedNode *root)  {
    if ( nullptr == root ) { return 0; }
    return checkHeight(root->left_) - checkHeight(root->right_);
}


//template<class T, class S>
avlRankedNode* avlRanked::leftRotation(avlRankedNode *node) {
    avlRankedNode* B = node;
    avlRankedNode* A = node->right_;

    int originAr = (A->right_ != nullptr) ? A->right_->w : 0;
    int originAl = (A->left_ != nullptr) ? A->left_->w : 0;
    int originBl = (B->left_ != nullptr) ? B->left_->w : 0;

    B->right_ = A->left_;
    if ( A->left_){
        A->left_->parent_ = B;
    }

    A->parent_ = B->parent_; //Set A as the new root

    A->left_ = B;

    //Checking if B was left or right child.
    if ( B->parent_){
        if(  B->parent_->right_ == B ){
            B->parent_->right_ = A;
        }
        else {
            B->parent_->left_ = A;
        }
    }

    B->parent_ = A;
    B->height = findHeight(B);
    A->height = findHeight(A);

    B->w = originAl + originBl + 1;
    A->w = originAr + B->w + 1;

    return A;
}

//template<class T, class S>
avlRankedNode* avlRanked::rightRotation(avlRankedNode *node) {
    avlRankedNode* B = node;
    avlRankedNode* A = node->left_;

    int originAr = (A->right_ != nullptr) ? A->right_->w : 0;
    int originAl = (A->left_ != nullptr) ? A->left_->w : 0;
    int originBr = (B->right_ != nullptr) ? B->right_->w : 0;

    B->left_ = A->right_;
    if ( A->right_){
        A->right_->parent_ = B;
    }

    A->parent_ = B->parent_; //Set A as the new root

    A->right_ = B;

    //Checking if B was left or right child.
    if ( B->parent_){
        if(  B->parent_->left_ == B ){
            B->parent_->left_ = A;
        }
        else {
            B->parent_->right_ = A;
        }
    }


    B->parent_ = A;
    B->height = findHeight(B);
    A->height = findHeight(A);


    B->w = originAr + originBr + 1;
    A->w = originAl + B->w + 1;

    return A;
}

//template<class T, class S>
void avlRanked::printTest(avlRankedNode* root) {
    if( !root ) return;
    printTest(root->left_);
    printTest(root->right_);
    return;
}

//template<class T, class S> ////Added removeArtistMethod as bool to change the pointers inside the list of the songs while deleting the song from the tree
void avlRanked::cleantree() {
    deleteTree(root_);
    root_=nullptr;
    minNode_=nullptr;
}
// Swaps between to nodes in the tree
//template<class T, class S>
void avlRanked::swap(avlRankedNode *A, avlRankedNode *B) {
    avlRankedNode* temp = new avlRankedNode(); //TODO: Deleted this line of new because of a bug in library1.cpp
    if(!temp) { throw allocationError(); }

    temp->parent_ = A->parent_;
    temp->right_ = A->right_;
    temp->left_ = A->left_;
    if ( A->parent_){
        if(  A->parent_->right_ == A ){
            A->parent_->right_ = temp;
        }
        else {
            A->parent_->left_ = temp;
        }
    }
    if ( A->right_){
        A->right_->parent_ = temp;
    }
    if( A->left_){
        A->left_->parent_ = temp;
    }
    A->parent_ = B->parent_;
    A->right_ = B->right_;
    A->left_ = B->left_;
    if ( B->parent_){
        if(  B->parent_->right_ == B ){
            B->parent_->right_ = A;
        }
        else {
            B->parent_->left_ = A;
        }
    }
    if ( B->right_){
        B->right_->parent_ = A;
    }
    if( B->left_){
        B->left_->parent_ = A;
    }

    B->parent_ = temp->parent_;
    B->right_ = temp->right_;
    B->left_ = temp->left_;

    if ( temp->parent_){
        if(  temp->parent_->right_ == temp ){
            temp->parent_->right_ = B;
        }
        else {
            temp->parent_->left_ = B;
        }
    }
    if ( temp->right_){
        temp->right_->parent_ = B;
    }
    if( temp->left_){
        temp->left_->parent_ = B;
    }


    temp->parent_=nullptr;
    temp->right_=nullptr;
    temp->left_=nullptr;
    delete temp;

    return;
}

//template<class T, class S>
avlRankedNode *avlRanked::climb(int m) {
    if (m <=0 ) { return nullptr; }
    double bla = (log2 (m)) + 1;
    int logm = floor(bla);
    avlRankedNode* temp = minNode_;
    while(temp->parent_ && logm != 0){
        temp = temp->parent_;
        logm--;
    }
    return temp;
}

//template<class T, class S>
bool avlRanked::isEmpty() {
    return !(root_);
}

//template<class T, class S>
avlRankedNode *avlRanked::select(avlRankedNode *root, int k) {
    if (!root) { return nullptr; }
    if(((root->left_ != nullptr) ? root->left_->w : 0) == k-1){
        return root;
    }
    else if (((root->left_ != nullptr) ? root->left_->w : 0) > k-1 ){
        return select(root->left_,k);
    }
    else{
        return select(root->right_,(k - ((root->left_ != nullptr) ? root->left_->w : 0) -1));
    }
}

//template<class T, class S>
int avlRanked::getsize() {
    return size_;
}

