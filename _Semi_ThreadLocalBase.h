//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW//
//																																			//
//	PROJECT SEMI: _Semi_ThreadLocalBase.h																										//
//																																			//
//	Library Port - ThreadLocal																										//
//																																			//
//	Last upate : 2018/02/08																													//
//	Version    : 1.0.1																														//
//	C++ Version: 17																															//
//																																			//
//	Copyright (C) 2018, Sugwan Kim, <tnrhkssla@gmail.com>																					//
//																																			//
//	You may opt to use, copy, modify, merge, publish, distribute and/or sell copies of the Software, and permit persons to whom the			//
//  Software is	furnished to do so, under the terms of the COPYING file.																	//
//																																			//
//	This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.								//
//																																			//
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW//

#pragma once

#include <Semi_Combtype.h>

namespace Semi
{
	namespace _Base
	{
		//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW//

		class _ThreadLocalBase
		{
		protected:
			static constexpr Size TableBit = 10;
			static constexpr Uint32 Mask = (1 << static_cast<Uint32>(TableBit)) - 1;

			struct NodeBase
			{
				Uint32 Key;
				NodeBase() : Key(0) { }
			};

			template <typename Type_> struct Node : public NodeBase
			{
				Semi_inherit_arithmetic(Type_);

				Type_  Value;

				Node() { }
				Node(const Type_& value) : Value(value) { }
			};

			class alignas(16) Bucket
			{
				NodeBase* Data;
				Size  Unum;
				Size  Tnum;

				Semi_dll_port Void InitInternal(Size nodesize, Size nodealign);
			public:
				template <typename Type_> static Void Increse(Bucket* bucket, const NodeBase& basic_value, NodeBase* new_buffer)
				{
					Combtype<Node<Type_>>::MoveInstance(static_cast<Node<Type_>*>(new_buffer), static_cast<const Node<Type_>*>(bucket->Data), bucket->Tnum);
					for (Size i = bucket->Tnum; i < new_tnum; i++)
						Combtype<Node<Type_>>::CopyConstructor(static_cast<Node<Type_>*>(new_buffer)[i], static_cast<const Node<Type_>&>(basic_value));
				}

				Semi_dll_port NodeBase& Semi_vectorcall Find(Uint32 key, const NodeBase& basic_value, Void(*increse)(Bucket*, const NodeBase&, NodeBase*), Size nodesize, Size nodealign);

				template <typename Type_> Void Init(const Node<Type_>& basic_value)
				{
					InitInternal(sizeof(Node<Type_>), alignof(Node<Type_>));
					Combtype<Node<Type_>>::CopyConstructor(static_cast<Node<Type_>*>(Data)[0], basic_value);
				}
			};

			Semi_dll_port static Uint32 GetThreadID();
			Semi_dll_port Void InitTable(Bucket*& table);
		};

		//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW//

		template <typename Type_> class ThreadLocalBase : public _ThreadLocalBase
		{
			Node<Type_> BasicValue;
		protected:
			ThreadLocalBase(const Type_& basic_value, Bucket*& table) : BasicValue(basic_value)
			{
				InitTable(table);
				static constexpr Size n = (Size)1 << TableBit;
				const Bucket* end = table + n;
				for (Bucket* i = table; i < end; i++) i->Init<Type_>(BasicValue);
			}

			Type_& Get(Bucket* table)
			{
				return table[key & Mask].Find(GetThreadID(), BasicValue, Bucket::Increse<Type_>, sizeof(Node<Type_>), alignof(Node<Type_>));
			}
		};
	}
}

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW//
