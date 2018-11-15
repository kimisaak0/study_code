#define  _CRT_SECURE_NO_WARNINGS

#pragma once

#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <iostream>


SQLRETURN HandleDiagnosticRecord();

int Init();

static WCHAR* GetMtW(const char* data);

void Select();

void Select_2(const char* name);

void Add(const char* name, const char* pass);

void Delete(const char* name);

void Update(const char* name);

void run();