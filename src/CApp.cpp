#include "CApp.h"

CApp::CApp(){
}

int CApp::OnExecute(){
	return 0;
}

int main(int argc, char* args[]){
	CApp() theApp;
	return theApp.OnExecute();
}
