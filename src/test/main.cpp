#include <iostream>

#include "lotus/lotus.h"

using namespace lotus;

int main(int argc, char *argv[]) {
	
	
	Engine engine;
	engine.SetTargetUpdateRate(120);
	engine.SetTargetRenderRate(60);
	
	DisplayConfiguration config;
	config.maximized = true;
	engine.GetDisplay().SetConfiguration(config);
	
	
	
	engine.Start();
	
}