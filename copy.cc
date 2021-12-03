
#include <iostream>
#include <memory>
class parent  {
        public:
        int x = 3;
        parent(){}
/*         parent(const parent& p) {
                x=10;
                std::cout<< "parent copy" <<std::endl;
        } */
        virtual std::shared_ptr<parent> clone() =0;
};
class child : public parent {
        public:
        int y = 1;
        child(){}
        child(const child& c) {
                x = 4;
                y = 10;
        }
        virtual std::shared_ptr<parent> clone() {
            std::cout << " x " << this->x << " y " << y <<std::endl;
            return std::shared_ptr<parent>(new child(*this));
        }
};
int main(){
        std::shared_ptr<child> c1 = std::make_shared<child>();
        std::cout << " " << std::endl;
        std::shared_ptr<parent> ptr = c1.get()->clone();
        // std::shared_ptr<parent> c2 = std::make_shared<parent>(*c1);
}
