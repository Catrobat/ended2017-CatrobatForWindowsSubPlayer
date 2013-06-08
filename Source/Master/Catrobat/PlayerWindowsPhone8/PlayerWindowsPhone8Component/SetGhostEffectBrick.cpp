#include "pch.h"
#include "SetGhostEffectBrick.h"
#include "Script.h"
#include "Object.h"
#include "Interpreter.h"

SetGhostEffectBrick::SetGhostEffectBrick(string spriteReference, FormulaTree *transparency, Script *parent) :
	Brick(TypeOfBrick::SetGhostEffectBrick, spriteReference, parent),
	m_transparency(transparency)
{
}

void SetGhostEffectBrick::Execute()
{
	m_parent->Parent()->SetTransparency(0.0f);
}