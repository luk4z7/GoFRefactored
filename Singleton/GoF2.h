#pragma once

#include <list>

namespace SingletonPattern::GoF2
{
	class NameSingletonPair {};

	class Singleton {
	public:
		static void Register(const char* name, Singleton*) {}
		static Singleton* Instance();
	protected:
		static Singleton* Lookup(const char* name) { return 0; }
	private:
		static Singleton* _instance;
		static std::list<NameSingletonPair>* _registry;
	};

	Singleton* Singleton::_instance = 0;

	Singleton* Singleton::Instance() {
		if (_instance == 0) {
			const char* singletonName = getenv("SINGLETON");
			// user or environment supplies this at startup 

			_instance = Lookup(singletonName);
			// Lookup returns 0 if there's no such singleton 
		}
		return _instance;
	}

	class MySingleton : public Singleton
	{
		MySingleton();
	};

	MySingleton::MySingleton() {
		// ... 
		Singleton::Register("MySingleton", this);
	}

	static MySingleton* theSingleton = 0;
}
