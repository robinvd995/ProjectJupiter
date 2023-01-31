#pragma once

#include "JupiterCoreDefinitions.h"

#include <vector>

#define JUPITER_SIGN_EVENT \
private: \
static int getEventSignature() { return m_EventSignature; } \
static void setEventSignature(int signature) { m_EventSignature = signature; } \
static int m_EventSignature; \
friend class EventHandler

#define JUPITER_DEFINE_EVENT(e) int e::m_EventSignature = UINT_MAX

namespace Jupiter {

    /// <summary>
    /// Generic Jupiter Event class, all events should inherit this class
    /// </summary>
    class JEvent {
    public:
        virtual ~JEvent() = default;

        /// <summary>
        /// Marks this event as handled and will not be passed to follow event listeners
        /// </summary>
        void markHandled() { m_Handled = true; }

    protected:
        bool m_Handled = false;

        friend class EventDispatcher;
    };

    /// <summary>
    /// typedef for the event listener function
    /// </summary>
    typedef void (*EventListenerFunc)(JEvent* e);

    /// <summary>
    /// Struct to contain the event listener function and priority given to the listener
    /// </summary>
    struct EventListener {
        uint m_ListenerPriority;
        EventListenerFunc m_ListenerFunc;

        EventListener() = delete;
        EventListener(uint priority, EventListenerFunc func);
        ~EventListener() = default;
    };

    /// <summary>
    /// Class used to dispatch the events to the registered listeners
    /// </summary>
    class EventDispatcher {

    public:
        EventDispatcher() = delete;
        EventDispatcher(int eventSignature);
        ~EventDispatcher() {}

        /// <summary>
        /// 
        /// </summary>
        /// <param name="priority"></param>
        /// <param name="listenerFunc"></param>
        void addListener(uint priority, EventListenerFunc listenerFunc);

        /// <summary>
        /// TODO
        /// </summary>
        void removeListener();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        void publishEvent(JEvent* e);

    private:
        int m_EventSignature;
        std::vector<EventListener> m_Listeners;
    };

    /// <summary>
    /// 
    /// </summary>
    class EventDispatcherDelayed {

    };

    /// <summary>
    /// Entry struct for the event register
    /// </summary>
    struct EventRegisterEntry {
        uint m_EventSignature;
        EventDispatcher m_EventDispatcher;

        EventRegisterEntry() = delete;
        EventRegisterEntry(uint signature);
        ~EventRegisterEntry() = default;
    };

    /// <summary>
    /// 
    /// </summary>
    class EventHandler {

    public:
        EventHandler() = default;
        ~EventHandler() = default;

        /// <summary>
        /// Register an event
        /// </summary>
        /// <typeparam name="T">The class type of the event to register</typeparam>
        /// <returns>The signature of the event</returns>
        template<typename T>
        int registerEvent() {
            if (T::getEventSignature() != UINT_MAX) {
                return T::getEventSignature();
            }

            uint signature = m_NextSignature++;

            try {
                EventRegisterEntry& reg = m_EventRegister.at(signature);
                std::cout << "ERROR WHILE REGISTERING EVENT!" << std::endl;
            }
            catch (std::exception e) {}

            T::setEventSignature(signature);
            m_EventRegister.push_back({ signature });
            return T::getEventSignature();
        }

        /// <summary>
        /// Register an event listener
        /// </summary>
        /// <typeparam name="T">The event to subscribe to</typeparam>
        /// <param name="func">The function to be called when an event is posted</param>
        /// <param name="priority">The priority this listener takes compared to other listeners</param>
        template<typename T>
        void registerListener(EventListenerFunc func, uint priority = 0) {
            uint eventSignature = T::getEventSignature();
            try {
                EventRegisterEntry& reg = m_EventRegister.at(eventSignature);
                reg.m_EventDispatcher.addListener(priority, func);
            }
            catch (std::exception e) {
                std::cout << "ERROR WHILE REGISTERING EVENT LISTENER!" << std::endl;
            }
        }

        /// <summary>
        /// Post an event, ready to be dispatched
        /// </summary>
        /// <typeparam name="T">The event type to be posted</typeparam>
        /// <param name="e">The event object</param>
        template<typename T>
        void postEvent(JEvent* e) {
            uint eventSignature = T::getEventSignature();
            try {
                EventRegisterEntry& reg = m_EventRegister.at(eventSignature);
                reg.m_EventDispatcher.publishEvent(e);
            }
            catch (std::exception e) {
                std::cout << "ERROR WHILE POSTING EVENT!" << std::endl;
            }
        }

    private:
        int m_NextSignature = 0;
        std::vector<EventRegisterEntry> m_EventRegister;
    };
}

// IMPLEMENTATION EXAMPLE
// 
// class Event0 : public JEvent {
//     SIGN_EVENT;
// public:
//     Event0() = delete;
//     Event0(const std::string& val) : m_Message(val) {}
//     virtual ~Event0() = default;
// 
//     void handle() { std::cout << "Event0 Message: " << m_Message << std::endl; }
// 
// private:
//     std::string m_Message;
// };
// 
// class Event1 : public JEvent {
//     SIGN_EVENT;
// public:
//     Event1() = delete;
//     Event1(uint val) : m_Val(val) {}
//     virtual ~Event1() = default;
// 
//     void print() { std::cout << "Event1 Number: " << m_Val << std::endl; }
// 
// private:
//     uint m_Val;
// };
// 
// DEFINE_EVENT(Event0);
// DEFINE_EVENT(Event1);
// 
// static void listenerEvent0(Event* e) {
//     Event0& evnt = *(Event0*)e;
//     evnt.handle();
// }
// 
// static void listenerEvent1(Event* e) {
//     Event1& evnt = *(Event1*)e;
//     evnt.print();
// }
// 
// int main() {
// 
//     EventHandler handler;
//     int event0id = handler.registerEvent<Event0>();
//     int event1id = handler.registerEvent<Event1>();
// 
//     handler.registerListener<Event0>(listenerEvent0, 0);
//     handler.registerListener<Event1>(listenerEvent1, 0);
// 
//     Event0 e0("Hello world!");
//     Event1 e1(24);
// 
//     handler.postEvent<Event0>(&e0);
//     handler.postEvent<Event1>(&e1);
// }
