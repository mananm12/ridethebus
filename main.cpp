//
//  main.cpp
//  ridethebus
//
//  Created by Manan Manchanda on 10/8/21.
//

#include <iostream>
#include <random>
#include "ridethebus.hpp"
#include "xcode_redirect.hpp"
#include <ctime>

int main(int argc, char * argv[]) {
    xcode_redirect(argc, argv);
    RideBus newGame;
    newGame.processCommandLine(argc, argv);
    newGame.play();
}
