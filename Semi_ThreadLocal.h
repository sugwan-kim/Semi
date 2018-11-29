//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW//
//																																			//
//	PROJECT SEMI: Semi_ThreadLocal.h																										//
//																																			//
//	Library Port - ThreadLocal																										//
//																																			//
//	Last upate : 2018/11/29																													//
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

#include <_Semi_ThreadLocalBase.h>

namespace Semi
{
	//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW//
	//																																		//
	//		ThreadLocal																														//
	//																																		//
	//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW//
#ifdef Semi_visual_studio

	// l
	// ***** �����庰 �����
	// l
	// c++ - thread_local �� ���� ������ �Ѵ�, ȣȯ�� �� ����ȭ�� ���� ����
	template <typename Type_, Size Index_> class ThreadLocal
	{
		static thread_local Type_ Core;
	public:
		ThreadLocal(const Type_& basic_value = Type_()) { Core = basic_value; }

		operator Type_&() { return Core; }
	};

	template <typename Type_, Size Index_> thread_local Type_ ThreadLocal<Type_, Index_>::Core;
#else // �ٸ� �����Ϸ��� thread_local Ű���带 ���������� �����𸣰� ������.

	// l
	// ***** �����庰 �����
	// l
	// c++ - thread_local �� ���� ������ �Ѵ�, ȣȯ�� �� ����ȭ�� ���� ����
	template <typename Type_, Size Index_> class ThreadLocal : public _Base::ThreadLocalBase<Type_>
	{
		static _Base::ThreadLocalBase<Type_>::Bucket* Table;
	public:
		ThreadLocal(const Type_& basic_value = Type_()) : _Base::ThreadLocalBase<Type_>(basic_value, Table) { }

		operator Type_&() { return this->Get(Table); }
	};

	template <typename Type_, Size Index_> typename _Base::ThreadLocalBase<Type_>::Bucket* ThreadLocal<Type_, Index_>::Table;
#endif
	//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW//
	//																																		//
	//		ThreadLocalSlow																													//
	//																																		//
	//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW//

	// l
	// ***** �����庰 �����
	// l
	// c++ - thread_local �� ���� ������ �Ѵ�, ȣȯ�� �� ����ȭ�� ���� ����
	// �������� ThreadLocal�� �ٸ��� �ε����� �ʿ���� �޸𸮸� ���� �����Ѵ�
	template <typename Type_> class ThreadLocalSlow : public _Base::ThreadLocalBase<Type_>
	{
		_Base::ThreadLocalBase<Type_>::Bucket* Table;
	public:
		ThreadLocalSlow(const Type_& basic_value = Type_()) : _Base::ThreadLocalBase<Type_>(basic_value, Table) { }

		operator Type_&() { return this->Get(Table); }
	};
}

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW//
