// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <Hello.h>

using namespace std;

namespace
{

class HelloI : public Demo::Hello
{
public:

    virtual void 
    sayHello(const Ice::Current& current)
    {
        current.adapter->getCommunicator()->getLogger()->print("Hello World!");
    }

    virtual void 
    shutdown(const Ice::Current& current)
    {
        current.adapter->getCommunicator()->getLogger()->print("Shutting down...");
        current.adapter->getCommunicator()->shutdown();
    }
};


class HelloPluginI : public Ice::Plugin
{
public:

     HelloPluginI(const Ice::CommunicatorPtr& communicator) : 
         _communicator(communicator)
     {
     }

     void
     initialize()
     {
         Ice::ObjectAdapterPtr adapter = _communicator->createObjectAdapter("Hello");
         adapter->add(new HelloI, Ice::stringToIdentity("hello"));
         adapter->activate();
     }

     void
     destroy()
     {
     }

private:

    Ice::CommunicatorPtr _communicator;
};

};

extern "C"
{

ICE_DECLSPEC_EXPORT ::Ice::Plugin*
createHello(const Ice::CommunicatorPtr& communicator, const string&, const Ice::StringSeq&)
{
    return new HelloPluginI(communicator);
}

}
