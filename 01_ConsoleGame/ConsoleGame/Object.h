#pragma once

class Object
{
public:
	virtual void Init() = 0;	// 초기화
	virtual void Update() = 0;	// 이벤트 처리(로직 연산)
	virtual void Render() = 0;  // 그리기
	virtual void Release() = 0; // 메모리 해제

public:
	Object() {}
	virtual ~Object() {}
};