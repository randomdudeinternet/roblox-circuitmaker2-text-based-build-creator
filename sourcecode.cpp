#include <iostream>
#include <string>
enum types { Nor = 0, And = 1, Or = 2, Xor = 3, flip = 5 };
char objects[30000];
int currentfreespace = 0;
int currentindex = 1;
bool wired = true;
struct object {
    object()
        :x(0), y(0), z(0), is_on(0), type(0), index(currentindex), hasconsecutiveblock(true), hasconsecutiveblockrepresenter("\0")
    {
        currentindex += 1;
    }
    short x, y, z, is_on; // please keep your values between -32 768 and 32 767 since otherwise they will overflow
    short type;
    int index;
    bool hasconsecutiveblock;

private:
    std::string hasconsecutiveblockrepresenter;
public:
    void create() {
        hasconsecutiveblockrepresenter = hasconsecutiveblock ? hasconsecutiveblockrepresenter = ";" : hasconsecutiveblockrepresenter = "\0";
        std::string mainstring = std::to_string(type) + std::string(",") + std::to_string(is_on) + std::string(",") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(",") + std::to_string(z) + std::string(",");
        for (int i = 0; i < mainstring.size(); i++) {
            objects[currentfreespace] = mainstring[i];
            currentfreespace++;
        }
        if (type == flip && is_on == 1 && !wired) {
            objects[currentfreespace] = '2';
            objects[currentfreespace + 1] = '+';
            objects[currentfreespace + 2] = '0';
            currentfreespace += 3;
        }
        if (type == flip && is_on == 0 && wired) {
            objects[currentfreespace] = '0';
            objects[currentfreespace + 1] = '+';
            objects[currentfreespace + 2] = '0';
            currentfreespace += 4;
        }
        if (type == flip && is_on == 1 && wired) {
            objects[currentfreespace] = '2';
            objects[currentfreespace + 1] = '+';
            objects[currentfreespace + 2] = '0';
            currentfreespace += 4;
        }
        if (type == flip && is_on == 0 && !wired) {
            objects[currentfreespace] = '0';
            objects[currentfreespace + 1] = '+';
            objects[currentfreespace + 2] = '0';
            currentfreespace += 3;
        }
        if (!hasconsecutiveblock && !wired) {
            for (int i = 0; i < 3; i++) {
                objects[currentfreespace] = '?';
                currentfreespace += 1;
            }
        }
      for(int i = 0; i < hasconsecutiveblockrepresenter.size(); i++){
        objects[currentfreespace] = hasconsecutiveblockrepresenter[i];
        currentfreespace++;
      }
    }
};
void createwire(object a, object b, bool hasmorewires, bool is_starting_wire, bool is_ending_wire) {
    std::string index1 = std::to_string(a.index);
    std::string index2 = std::to_string(b.index);
    if (hasmorewires == false) {
        objects[currentfreespace] = '?';
        if (index1.size() >= index2.size()) {
            for (int i = 0; i < index1.size(); i++) {
                objects[currentfreespace + 1 + i] = index1[i];
                if (i < index2.size()) {
                    objects[currentfreespace + 2 + i + index1.size()] = index2[i];
                }
            }
        }
        else {
            for (int i = 0; i < index2.size(); i++) {
                objects[currentfreespace + 1 + i] = index2[i];
                if (i < index1.size()) {
                    objects[currentfreespace + 2 + i + index2.size()] = index1[i];
                }
            }
        }
        objects[currentfreespace + index1.size() + index2.size()] = ',';
        objects[currentfreespace + index1.size() + index2.size() + 2] = '?';
        objects[currentfreespace + index1.size() + index2.size() + 3] = '?';
        currentfreespace += index1.size() + (index2.size() * 2) + 4;
        return;
    }
    if (is_starting_wire == true) {
        objects[currentfreespace] = '?';
        if (index1.size() >= index2.size()) {
            for (int i = 0; i < index1.size(); i++) {
                objects[currentfreespace + 1 + i] = index1[i];
                if (i < index2.size()) {
                    objects[currentfreespace + 2 + i + index1.size()] = index2[i];
                }
            }
        }
        else {
            for (int i = 0; i < index2.size(); i++) {
                objects[currentfreespace + 1 + i] = index2[i];
                if (i < index1.size()) {
                    objects[currentfreespace + 2 + i + index2.size()] = index1[i];
                }
            }
        }
        objects[currentfreespace + index1.size() + index2.size()] = ',';
        objects[currentfreespace + index1.size() + index2.size() + 2] = ';';
        currentfreespace += index1.size() + index2.size() + 3;
        return;
    }
    if (is_ending_wire == true) {
        if (index1.size() >= index2.size()) {
            for (int i = 0; i < index1.size(); i++) {
                objects[currentfreespace + i] = index1[i];
                if (i < index2.size()) {
                    objects[currentfreespace +1+ i + index1.size()] = index2[i];
                }
            }
        }
        else {
            for (int i = 0; i < index2.size(); i++) {
                objects[currentfreespace + 1 + i] = index2[i];
                if (i < index1.size()) {
                    objects[currentfreespace +1+ i + index2.size()] = index1[i];
                }
            }
        }
        objects[currentfreespace + index1.size() + index2.size()-1] = ',';
        objects[currentfreespace + index1.size() + index2.size() + 2] = '?';
        objects[currentfreespace + index1.size() + index2.size() + 3] = '?';
        currentfreespace += index1.size() + index2.size() + 4;
        return;
    }
    if (hasmorewires) {
        if (index1.size() >= index2.size()) {
            for (int i = 0; i < index1.size(); i++) {
                objects[currentfreespace + i] = index1[i];
                if (i < index2.size()) {
                    objects[currentfreespace + 1 + i + index1.size()] = index2[i];
                }
            }
        }
        else {
            for (int i = 0; i < index2.size(); i++) {
                objects[currentfreespace + 1 + i] = index2[i];
                if (i < index1.size()) {
                    objects[currentfreespace + 2 + i + index2.size()] = index1[i];
                }
            }
        }
        objects[currentfreespace + index1.size() + index2.size()-1] = ',';
        objects[currentfreespace + index1.size() + index2.size() + 1] = ';';
        currentfreespace += index1.size() + index2.size() + 2;
        return;
    }
}
int main() {
    for (int i = 0; i < currentfreespace; i++) {
        std::cout << objects[i];
    }
    std::cout << "\0" << std::endl;
    return 0;
}