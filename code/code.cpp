#include <iostream>
#include <string>
enum types{Nor = 0, And = 1, Or = 2, Xor = 3, flip = 5};
static unsigned char objects[100][20];
static short currentobj = 0;

struct object{
  // also don't make any value bigger than 9
  short x = 0,y = 0,z = 10, is_on = 0; // unknown is a value that i cold not find out what it meant. change this if something goes wrong
  short type = -1;
  short index = 1; // please set it to be the object id and it has to be continious if not it will probrably break the compiler 
  bool wired = false;// change this to wire stuff
  char hasconsecutiveblock = ',';
 void create(){
  createbase();
  if(wired == false && type != flip && hasconsecutiveblock == ','){
    objects[currentobj][10] = '?';
    objects[currentobj][11] = '?';
    objects[currentobj][12] = '?';
  }
  if(wired == false && type == flip && is_on == false && hasconsecutiveblock == ','){
    objects[currentobj][10] = '0';
    objects[currentobj][11] = '+';
    objects[currentobj][12] = '0';
    objects[currentobj][13] = '?';
    objects[currentobj][14] = '?';
    objects[currentobj][15] = '?';
  }
  if(wired == false && type == flip && is_on == true && hasconsecutiveblock == ','){
    objects[currentobj][10] = '0';
    objects[currentobj][11] = '+';
    objects[currentobj][12] = '2';
    objects[currentobj][13] = '?';
    objects[currentobj][14] = '?';
    objects[currentobj][15] = '?';
  }
  currentobj += 1;
 }



 private:




 void createbase(){ // this function creates the base block input also if u have another block then set has consecutive block to be ;
 std::string s_type = std::to_string(type);
 std::string s_ison = std::to_string(is_on); // the s_ stands for stringficated
 std::string s_x = std::to_string(x);
 std::string s_y = std::to_string(y);
 std::string s_z = std::to_string(z);
 for(int i = 0; i < s_type.size(); i++){
  objects[currentobj][i] = s_type[i];
 }
 for(int i = 0; i < s_ison.length(); i++){
  objects[currentobj][i + s_type.size()+1] = s_ison[i];
 }
 for(int i = 0; i < s_x.size(); i++){
  objects[currentobj][i + s_type.size()+s_ison.size()+2] = s_x[i];
 }
 for(int i = 0; i < s_y.size(); i++){
  objects[currentobj][i + s_type.size()+s_ison.size()+s_x.size()+3] = s_y[i];
 }
 for(int i = 0;i < s_z.size(); i++){
  objects[currentobj][i + s_type.size() + s_ison.size() + s_x.size() + s_y.size() + 4] = s_z[i];
 }
  objects[currentobj][s_type.size()] = ',';
  objects[currentobj][s_type.size()+s_ison.size()+1] = ',';
  objects[currentobj][s_type.size()+s_ison.size()+s_x.size()+2] = ',';
  objects[currentobj][s_type.size()+s_ison.size()+s_x.size()+s_y.size()+3] = ',';
  objects[currentobj][s_type.size()+s_ison.size()+s_x.size()+s_y.size()+s_z.size()+4] = ',';
  if(type == flip && hasconsecutiveblock == ';'){
    objects[currentobj][s_type.size()+s_ison.size()+s_x.size()+s_y.size()+s_z.size()+5] = '2';
    objects[currentobj][s_type.size()+s_ison.size()+s_x.size()+s_y.size()+s_z.size()+6] = '+';
    objects[currentobj][s_type.size()+s_ison.size()+s_x.size()+s_y.size()+s_z.size()+7] = '0';
    objects[currentobj][s_type.size()+s_ison.size()+s_x.size()+s_y.size()+s_z.size()+8] = ';';
  }
  if(hasconsecutiveblock == ';' && type != flip){
    objects[currentobj][s_type.size()+s_ison.size()+s_x.size()+s_y.size()+s_z.size()+5] = ';';
  }
}
};

void createwiredata(unsigned short index1,unsigned short index2, bool hasmorewires, bool is_startingwire, bool is_endingwire){
    std::string s_index1 = std::to_string(index1);
    std::string s_index2 = std::to_string(index2);
  if(hasmorewires == false && is_endingwire == false){
    for(int i = 0; i < s_index1.size(); i++){
      objects[currentobj][i+1] = s_index1[i];
      if(i >= s_index2.size()){
        continue;
      }
      objects[currentobj][i+s_index1.size()+2] = s_index2[i];
    }
    objects[currentobj][0] = '?';
    objects[currentobj][s_index1.size()+1] = ',';
    objects[currentobj][s_index1.size()+s_index2.size()+2] = '?';
    objects[currentobj][s_index1.size()+s_index2.size()+3] = '?';
    return;
  }
  if(hasmorewires == true && is_startingwire){
    for(int i = 0; i < s_index1.size(); i++){
      objects[currentobj][i+1] = s_index1[i];
      if(i >= s_index2.size()){
        continue;
      }
      objects[currentobj][i+s_index1.size()+2] = s_index2[i];
    }
    objects[currentobj][0] = '?';
    objects[currentobj][s_index1.size()+1] = ',';
    objects[currentobj][s_index1.size()+s_index2.size()+2] = ';';
    return;
  }
  if(is_endingwire){
  for(int i = 0; i < s_index1.size(); i++){
  objects[currentobj][i] = s_index1[i];
  if(i >= s_index2.size()){
      continue;
    }
      objects[currentobj][i+s_index1.size()+1] = s_index2[i];
    }
    objects[currentobj][s_index1.size()] = ',';
    objects[currentobj][s_index1.size()+s_index2.size()+1] = '?';
    objects[currentobj][s_index1.size()+s_index2.size()+2] = '?';
    return;
  }
  for(int i = 0; i < s_index1.size(); i++){
  objects[currentobj][i] = s_index1[i];
  if(i >= s_index2.size()){
      continue;
    }
      objects[currentobj][i+s_index1.size()+1] = s_index2[i];
    }
    objects[currentobj][s_index1.size()+1] = ',';
    objects[currentobj][s_index1.size()+s_index2.size()+2] = ';';
}

int main(){
  objects[99][19] = '\0'; // this line of code is required
  
  for(int i = 0; i < 10; i++){
    std::cout << objects[i];
  }
}