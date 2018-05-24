#include "hello_world/hello_object.hh"
#include <iostream>
#include "debug/Hello.hh"
#include "base/logging.hh"

HelloObject::HelloObject(HelloObjectParams *params) :
    SimObject(params),
    // This is a C++ lambda. When the event is triggered, it will call the
    // processEvent() function. (this must be captured)
    event([this]{ processEvent(); }, name() + ".event"),
    goodbye(params->goodbye_object),
    myName(params->name),
    latency(params->time_to_wait),
    timesLeft(params->number_of_fires) {
    DPRINTF(Hello, "Created the hello object\n");
    panic_if(!goodbye, "HelloObject must have a non-null GoodbyeObject");
}

HelloObject* HelloObjectParams::create() {
  return new HelloObject(this);
}

void HelloObject::processEvent() {
    timesLeft--;
    DPRINTF(Hello, "Hello world! Processing the event! %d left\n",
                          timesLeft);

    if (timesLeft <= 0) {
        DPRINTF(Hello, "Done firing!\n");
        goodbye->sayGoodbye(myName);
    } 
    else {
        schedule(event, curTick() + latency);
    }
}

void HelloObject::startup() {
  schedule(event, latency);
}
