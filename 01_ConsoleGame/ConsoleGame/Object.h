#pragma once

class Object
{
public:
	virtual void Init() = 0;	// �ʱ�ȭ
	virtual void Update() = 0;	// �̺�Ʈ ó��(���� ����)
	virtual void Render() = 0;  // �׸���
	virtual void Release() = 0; // �޸� ����

public:
	Object() {}
	virtual ~Object() {}
};