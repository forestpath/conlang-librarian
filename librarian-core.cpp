//g++ -o librycore librarian-core.cpp
//librycore.exe

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

//add roots to a root library
void add_root_library( string input_data ){ //next edit: centralize library editing
    //check for repeats
    //string your_library_str = read_root_library();
    //int add_ind = your_library_str.find( input_data );
    //if( add_ind != string::npos ){
    //        cout << "Requested sound already in library" << endl;
    //    } else{
            ofstream rootslibry;
            rootslibry.open("roots-library.txt", ios_base::app);
            if( !rootslibry ){
                cout << "File edit error" << endl;
            } else{
                rootslibry << " ";
                rootslibry << input_data;
            }
            rootslibry.close();
    //}
}

//read sounds from a sound library
string read_sound_library(){
    string your_library_str = "";
    string your_cat = "";
    bool empty_libry = true;

    ifstream soundlibry;
    soundlibry.open("sounds-library.txt");
    if( !soundlibry ){
        cout << "File read error" << endl;
    } else{
        while( soundlibry >> your_cat ){
            empty_libry = false;
            your_library_str += your_cat + " ";
        }
    }
    soundlibry.close();

    if( empty_libry ){
        your_library_str = "[Library empty]";
    }

    return your_library_str;
}

//add or remove sounds from a sound library
void edit_sound_library( string input_data ){
    //stream input_data into vector
    istringstream iss(input_data);
    vector<string> 
    input_results( (istream_iterator<string>(iss)), 
    istream_iterator<string>() );

    if( input_results.size() != 2 ){ //error check input
        cout << "Input error" << endl;
        return;
    }

    //assign vector to vars
    string edit_mode = input_results[0];
    string edit_sound = input_results[1]; //next edit: multiple inputs

    if( edit_mode == "1" ){ //add sound
        //check for repeats
        string your_library_str = read_sound_library();
        int add_ind = your_library_str.find( edit_sound ); 
        if( add_ind != string::npos ){
            cout << "Requested sound already in library" << endl;
        } else{
            ofstream soundlibry;
            soundlibry.open("sounds-library.txt", ios_base::app);
            if( !soundlibry ){
                cout << "File edit error" << endl;
            } else{
                soundlibry << " ";
                soundlibry << edit_sound;
            }
            soundlibry.close();
        }
        
    } else if( edit_mode == "2" ){ //remove sound
        string your_library_str = read_sound_library();
        int del_ind = your_library_str.find( edit_sound ); 
        if( del_ind == string::npos ){
            cout << "Requested sound not in library" << endl;
        } else{
            string new_library_str = your_library_str.substr(0, del_ind) 
            + your_library_str.substr(del_ind + edit_sound.length() + 1, your_library_str.length());
            ofstream delsoundlibry;
            delsoundlibry.open("sounds-library.txt");
            delsoundlibry << new_library_str;
            delsoundlibry.close();
        }
        
    }
}

//all input collection
string get_input(){
    string input_data;
    cout << "-|";
    getline(cin, input_data);
    return input_data;
}

//full text interface
void interface(){
    bool exit_status = false;
    string input_data;
    int layer_state = 0; //for back button
    int type_state = 0; //for parallel states
    string your_library_str;

    cout << endl;
    cout << "(e) -> leave program" << endl;
    cout << "(^)    -> go back" << endl;

    while( !exit_status ){    
        if( layer_state == 0 ){
            cout << endl;
            cout << "Language selection" << endl;
            cout << "(1) -> Default" << endl;
            input_data = get_input();
            if( input_data == "1" ){
                layer_state = 1;
            }
        } else if( layer_state == 1 ){
            cout << endl;
            cout << "Layer selection" << endl;
            cout << "(1) -> Sounds" << endl;
            cout << "(2) -> Roots" << endl;
            cout << "(3) -> Words" << endl;
            input_data = get_input();
            if( input_data == "1" ){
                layer_state = 2;
                type_state = 1;
            } else if( input_data == "2" ){
                layer_state = 2;
                type_state = 2;
            } else if( input_data == "3" ){
                layer_state = 2;
                type_state = 3;
            }

        } else if( layer_state == 2 ){
            if( type_state == 1 ){
                cout << endl;
                cout << "Sound selection" << endl;
                cout << "b c d f g h j k l m n p r s t v w y z" << endl;
                cout << "ch th tth sh zh ng wh gh" << endl;
                cout << "a aw e ee i o oo u uh" << endl;
                cout << "Your library:" << endl;
                your_library_str = read_sound_library();
                cout << your_library_str << endl;
                cout << "(1 _) -> Add sound" << endl;
                cout << "(2 _) -> Remove sound" << endl;
                input_data = get_input();
                if( input_data != "^" && input_data != "e"){
                    edit_sound_library( input_data );
                }
            } else if( type_state == 2 ){
                cout << endl;
                cout << "Root selection" << endl;
                //
                input_data = get_input();
                if( input_data != "^" && input_data != "e"){
                    add_root_library( input_data );
                }
            } else if( type_state == 3 ){
                cout << endl;
                cout << "Word selection" << endl;
                //
                input_data = get_input();
            }
            
        }
        if( input_data == "^" && layer_state != 0 ){
            layer_state--;
        }
        if( input_data == "e" ){
            exit_status = true;
            cout << "Exiting" << endl;
        }
    }
}

//eldest function
int main(){

    interface();

    return 0;
}