#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int main(){
    fstream decrypted;
    fstream encrypted;
    string input;
    while(1){
        cout<<"3 options:\n(1)Encrypt the file decrypted.txt.\n(2)Decrypt the file encrypted.txt and display it's contents.\n(3)Write something into the file decrypted.\n(4)End program."<<endl;
        int option;
        cin>>option;
        cout<<endl;
        switch((int)option){
            case 1:
                decrypted.open("decrypted.txt",ios::in);
                encrypted.open("encrypted.txt",ios::out | ios::trunc);
                while(getline(decrypted,input)){
                    cout<<input<<endl;
                    for(unsigned int i=0;i<input.size();++i){
                        input[i]=(~input[i]);
                    }
                    encrypted<<input<<endl;
                }
                decrypted.close();
                encrypted.close();
                break;
            case 2:
                encrypted.open("encrypted.txt");
                while(getline(encrypted,input)){
                    for(unsigned int i=0;i<input.size();++i){
                        input[i]=(~input[i]);
                    }
                    cout<<input<<endl;
                }
                encrypted.close();
                break;
            case 3:
                decrypted.open("decrypted.txt",ios::out | ios::trunc);
                cin.ignore(1,'\n');
                getline(cin,input);
                decrypted<<input<<endl;
                decrypted.close();
                break;
            case 4:
                return 0;
            default:
                cout<<"Invalid option, try again."<<endl;
            break;
        }
    }
    return 0;
}
