
namespace ecs
{
	template<typename... T>
	struct list;

	template<template<typename... T>typename types>
	struct registry
	{
		//static const types types;
	};

	namespace internal
	{
		template<typename... Ts>
		struct registry_builder
		{
			using value = list<Ts...>;

			template<typename T>
			using add = registry_builder<T, Ts...>;
		};
	}

	using registry_builder = internal::registry_builder<>;
}