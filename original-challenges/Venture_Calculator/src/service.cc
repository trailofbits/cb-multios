/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "cstdlib.h"
#include "cstdio.h"
#include "cstring.h"
#include "cctype.h"
#include "types.h"

#ifdef DEBUG
  #define DBG(s, ...) fprintf(stderr, "DEBUG:\t" s "\n", ##__VA_ARGS__)
#else
  #define DBG(s, ...)
#endif

#define ASSERT(x, msg, ...) ({ \
    if (!(x)) \
    { \
      fprintf(stderr, "Assertion Failed: " msg "\n",  ##__VA_ARGS__); \
      _terminate(1); \
    } \
  })

static void WaitForInput(FILE* Stream, char* Input, u32 Max)
{
  fflush(stdout);
  memset(Input, Max, '\0');
  if (freaduntil(Input, Max, '\n', Stream) <= 0)
  {
    exit(0);
  }
}

static inline u8 CharToNum(char c)
{
  return digittoint(c);
}

static int CanBeDecimal(char* Token)
{
  if (*Token == '-')
    Token++;

  while (Token && *Token && (isdigit((char)*Token) || isspace((char)*Token)))
      Token++;

  if (Token && *Token == '\0')
    return 1;
  else
    return 0;
}

static int CanBeHex(char* Token)
{
  if (*Token == '-')
    Token++;

  while (Token && *Token && (isxdigit((char)*Token) || isspace((char)*Token)))
      Token++;

  if (Token && *Token == '\0')
    return 1;
  else
    return 0;
}

static int CanBeOctal(char* Token)
{
  if (*Token == '-')
    Token++;

  while (Token && *Token && ((isdigit((char)*Token) && CharToNum(*Token) < 8) || isspace(*Token)))
      Token++;

  if (Token && *Token == '\0')
    return 1;
  else
    return 0;
}

static int ParseInt(char* Token, s32* Value)
{
  long AsBase10 = CanBeDecimal(Token) ? strtol(Token, NULL, 10) : LONG_MIN;
  long AsBase16 = CanBeHex(Token) ? strtol(Token, NULL, 16) : LONG_MIN;
  long AsBase8 = CanBeOctal(Token) ? strtol(Token, NULL, 8) : LONG_MIN;

  if (AsBase10 != LONG_MIN && AsBase10 != LONG_MAX)
    *Value = AsBase10;
  else if (AsBase16 != LONG_MIN && AsBase16 != LONG_MAX)
    *Value = AsBase16;
  else if (AsBase8 != LONG_MIN && AsBase8 != LONG_MAX)
    *Value = AsBase8;
  else
    return -1;

  return 1;
}

template <typename t1>
struct Vector
{
  t1* _Storage;
  u32 _Capacity;
  u32 _Size;
  u32 _StepSize;

  Vector()
  {
    _Size = 0;
    _StepSize = 10;
    _Capacity = _StepSize;
    _Storage = new t1[sizeof(t1) * _Capacity];
  }

  Vector(u32 Cap) : _Capacity(Cap)
  {
    _Size = 0;
    _StepSize = 10;
    _Capacity = Cap;
    _Storage = new t1[sizeof(t1) * _Capacity];
  }

  ~Vector()
  {
    if (_Storage)
      delete[] _Storage;
  }

  t1& operator[] (const s32 StorageIndex)
  {
    return _Storage[StorageIndex];
  }

  void Append(t1 Value)
  {
    if (_Size == _Capacity)
    {
      _Grow();
    }

    _Storage[_Size] = Value;
    _Size += 1;
  }

  t1 Head(void)
  {
    ASSERT(_Size, "Getting head of empty vector");
    return _Storage[0];
  }

  t1 Last(void)
  {
    ASSERT(_Size, "Getting last of empty vector");
    return _Storage[_Size - 1];
  }

  t1 RemoveLast(void)
  {
    t1 Ret = Last();
    _Size--;

    if (_Capacity - _Size > _StepSize)
    {
      _Shrink();
    }

    return Ret;
  }

  int Empty(void)
  {
    return _Size == 0;
  }

  Vector* Copy(void)
  {
    Vector* VectorCopy = new Vector<t1>(_Capacity);
    VectorCopy->_Capacity = _Capacity;
    VectorCopy->_Size = _Size;
    VectorCopy->_StepSize = _StepSize;
    memcpy(VectorCopy->_Storage, _Storage, _Capacity * sizeof(t1));
    return VectorCopy;
  }

  void _Grow(void)
  {
    u32 NewCapacity = ((_Capacity / _StepSize) + 1) * _StepSize;
    t1* NewStorage = new t1[sizeof(t1) * NewCapacity];

    memcpy(NewStorage, _Storage, sizeof(t1) * _Capacity);

    delete[] _Storage;
    _Storage = NewStorage;
    _Capacity = NewCapacity;
  }

  void _Shrink(void)
  {
    u32 NewCapacity = _Capacity - _StepSize;
    t1* NewStorage = new t1[sizeof(t1) * NewCapacity];

    memcpy(NewStorage, _Storage, sizeof(t1) * NewCapacity);

    delete[] _Storage;
    _Storage = NewStorage;
    _Capacity = NewCapacity;
  }
};

template <typename t1>
struct Stack
{
  Vector<t1>* _BackingVector;

  void Push(t1 Value)
  {
    _BackingVector->Append(Value);
  }

  int Empty(void)
  {
    return _BackingVector->Empty();
  }

  int Size(void)
  {
    return _BackingVector->_Size;
  }

  t1 Pop(void)
  {
    ASSERT(!Empty(), "Popping off empty stack");
    return _BackingVector->RemoveLast();
  }

  t1 Peek(void)
  {
    ASSERT(!Empty(), "Peeking off empty stack");
    return _BackingVector->Last();
  }

  t1& operator[] (const s32 StorageIndex)
  {
    return (*_BackingVector)[_BackingVector->_Size - StorageIndex - 1];
  }

  Stack* Copy(void)
  {
    Stack<t1>* StackCopy = (Stack<t1> *)malloc(sizeof(Stack<t1>));
    StackCopy->_BackingVector = _BackingVector->Copy();
    return StackCopy;
  }

  void Invert(void)
  {
    for (size_t Index = 0; Index < Size() / 2; ++Index)
    {
      t1 Temp = _BackingVector->_Storage[Index];
      _BackingVector->_Storage[Index] = _BackingVector->_Storage[Size() - Index - 1];
      _BackingVector->_Storage[Size() - Index - 1] = Temp;
    }
  }

  Stack(u32 Cap)
  {
    _BackingVector = new Vector<t1>(Cap);
  }

  Stack()
  {
    _BackingVector = new Vector<t1>();
  }

  ~Stack()
  {
    if (_BackingVector)
    {
      delete _BackingVector;
    }
  }
};

struct VC
{
#define MAX_INPUT_SIZE 256
  u16 _MinHeight = 80;
  u16 _Width = 120;

  FILE* In;
  FILE* Out;

  char _InputBuffer[MAX_INPUT_SIZE];
  char _ErrorBuffer[MAX_INPUT_SIZE];
  int HasError;

  enum CommandReturn {
    ADD_HISTORY,
    NO_HISTORY,
    ERROR,
  };

  struct CommandEntry {
    const char* Name;
    u8 Arity;
    CommandReturn (VC::*F0)();
    CommandReturn (VC::*F1)(s32 v1);
    CommandReturn (VC::*F2)(s32 v1, s32 v2);
  };

  struct HistElem
  {
    Stack<s32>* CalcStack;
    const CommandEntry* Entry;
  };

  Stack<s32>* CalcStack = new Stack<s32>();
  Stack<HistElem>* HistStack = new Stack<HistElem>(64);

  static const u8 NumCommands = 29;
  const CommandEntry CommandTable[NumCommands] = {
    {"push", 1, NULL, &VC::ManualPush, NULL},

    { "+", 0, &VC::Add, NULL, NULL},
    { "-", 0, &VC::Sub, NULL, NULL},
    { "*", 0, &VC::Mul, NULL, NULL},
    { "/", 0, &VC::Div, NULL, NULL},
    { "!", 0, &VC::Fact, NULL, NULL},
    { "neg", 0, &VC::Neg, NULL, NULL},
    { "abs", 0, &VC::Abs, NULL, NULL},
    { "mod", 0, &VC::Mod, NULL, NULL},
    { "&", 0, &VC::And, NULL, NULL},
    { "|", 0, &VC::Or, NULL, NULL},
    { "^", 0, &VC::Xor, NULL, NULL},
    { "~", 0, &VC::Not, NULL, NULL},
    { "sum", 0, &VC::Sum, NULL, NULL},
    { "avg", 0, &VC::Avg, NULL, NULL},
    { "dup", 0, &VC::Dup, NULL, NULL},
    { "dupn", 0, &VC::DupN, NULL, NULL},
    { "dupn", 0, NULL, &VC::DupN, NULL},
    { "dupr", 0, &VC::DupR, NULL, NULL},
    { "dupr", 2, NULL, NULL, &VC::DupR},
    { "min", 0, &VC::Min, NULL, NULL},
    { "max", 0, &VC::Max, NULL, NULL},
    {"depth", 0, &VC::Depth, NULL, NULL},
    {"drop", 0, &VC::Drop, NULL, NULL},
    {"dropn", 0, &VC::DropN, NULL, NULL},
    {"dropn", 1, NULL, &VC::DropN, NULL},
    {"undo", 0, &VC::Undo, NULL, NULL},
    {"ivrt", 0, &VC::Invert, NULL, NULL},
    {"shuf", 0, &VC::Shuffle, NULL, NULL},
  };

  VC(FILE* In, FILE* Out) : In(In), Out(Out)
  {
    memset(_InputBuffer, '\0', MAX_INPUT_SIZE);
    memset(_ErrorBuffer, '\0', MAX_INPUT_SIZE);
    HasError = 0;
  }

  ~VC()
  {

    while (!CalcStack->Empty())
    {
      CalcStack->Pop();
    }

    fprintf(Out, "Bye bye\n");
    fflush(Out);
  }

  void ClearScreen(void)
  {
    fprintf(Out, "\033[2J\033[H");
  }

  void DrawScreen(void)
  {
    ClearScreen();
    s32 Height = _MinHeight > CalcStack->Size() ? _MinHeight : CalcStack->Size();
    for (s32 LineIndex = Height - 1; LineIndex >= 0; --LineIndex)
    {
      DrawLine(LineIndex);
    }

    if (HasError)
    {
      printf("%s", _ErrorBuffer);
      HasError = 0;
    }
    else
    {
      DrawFooter();
    }
  }

  void DrawLine(u32 LineIndex)
  {
    fprintf(Out, "%03d:\t", LineIndex);

    if (CalcStack->Size() > LineIndex)
    {
      fprintf(Out, "%d", (*CalcStack)[LineIndex]);
    }

    fprintf(Out, "\n");
  }

  void DrawFooter(void)
  {
    for (u32 Index = 0; Index < _Width; ++Index)
    {
      fprintf(Out, "-");
    }
    fprintf(Out, "\n");
  }

  const CommandEntry* FindCommand(char* Command, u8 Arity)
  {
    for (u8 CommandIndex = 0; CommandIndex < NumCommands; ++CommandIndex)
    {
      if (Arity == CommandTable[CommandIndex].Arity && strcmp(Command, CommandTable[CommandIndex].Name) == 0)
        return &CommandTable[CommandIndex];
    }

    return NULL;
  }

  void HandleCallResult(CommandReturn Value, const CommandEntry* Entry, HistElem* Hist)
  {
    switch (Value)
    {
      case ADD_HISTORY:
        {
          HistStack->Push(*Hist);
          break;
        }
      case NO_HISTORY:
        {
          break;
        }
      case ERROR:
        {
          break;
        }
    }
  }

  void HandleCall(const CommandEntry* Entry, s32 V1, s32 V2)
  {
    HistElem Hist = HistElem{CalcStack->Copy(), Entry};
    HandleCallResult(CallCommand(Entry, V1, V2), Entry, &Hist);
  }

  void HandleCall(const CommandEntry* Entry, s32 V1)
  {
    HistElem Hist = HistElem{CalcStack->Copy(), Entry};
    HandleCallResult(CallCommand(Entry, V1), Entry, &Hist);
  }

  void HandleCall(const CommandEntry* Entry)
  {
    HistElem Hist = HistElem{CalcStack->Copy(), Entry};
    HandleCallResult(CallCommand(Entry), Entry, &Hist);
  }

  CommandReturn CallCommand(const CommandEntry* Entry)
  {
    return (this->*Entry->F0)();
  }

  CommandReturn CallCommand(const CommandEntry* Entry, s32 V1)
  {
    return (this->*Entry->F1)(V1);
  }

  CommandReturn CallCommand(const CommandEntry* Entry, s32 V1, s32 V2)
  {
    return (this->*Entry->F2)(V1, V2);
  }

  void ErrorTooFewArgs(const char* Command)
  {
    sprintf(_ErrorBuffer, "Error: Too few arguments for '%s' command\n", Command);
    HasError = 1;
  }

  void ErrorInvalidInput(void)
  {
    sprintf(_ErrorBuffer, "Error: Invalid input\n");
    HasError = 1;
  }


  void PushValue(s32 Value)
  {
    CalcStack->Push(Value);
  }

  CommandReturn ManualPush(s32 Value)
  {
    CalcStack->Push(Value);
    return ADD_HISTORY;
  }

  CommandReturn Add(void)
  {
    if (CalcStack->Size() < 2)
    {
      ErrorTooFewArgs("+");
      return ERROR;
    }

    PushValue(CalcStack->Pop() + CalcStack->Pop());

    return ADD_HISTORY;
  }

  CommandReturn Sub(void)
  {
    if (CalcStack->Size() < 2)
    {
      ErrorTooFewArgs("-");
      return ERROR;
    }

    s32 V1 = CalcStack->Pop();
    s32 V2 = CalcStack->Pop();
    PushValue(V2 - V1);

    return ADD_HISTORY;
  }

  CommandReturn Mul(void)
  {
    if (CalcStack->Size() < 2)
    {
      ErrorTooFewArgs("*");
      return ERROR;
    }

    PushValue(CalcStack->Pop() * CalcStack->Pop());

    return ADD_HISTORY;
  }

  CommandReturn Div(void)
  {
    if (CalcStack->Size() < 2)
    {
      ErrorTooFewArgs("/");
      return ERROR;
    }

    s32 V1 = CalcStack->Pop();
    s32 V2 = CalcStack->Pop();

    if (V1 == 0)
    {
      ErrorInvalidInput();
      PushValue(V2);
      PushValue(V1);
      return ERROR;
    }

    PushValue(V2 / V1);

    return ADD_HISTORY;
  }

  CommandReturn Neg(void)
  {
    if (CalcStack->Size() < 1)
    {
      ErrorTooFewArgs("neg");
      return ERROR;
    }

    PushValue(-CalcStack->Pop());

    return ADD_HISTORY;
  }

  CommandReturn Fact(void)
  {
    if (CalcStack->Size() < 1)
    {
      ErrorTooFewArgs("!");
      return ERROR;
    }


    s32 Value = CalcStack->Pop();

    if (Value < 0 || Value > 1000)
    {
      ErrorInvalidInput();
      PushValue(Value);
      return ERROR;
    }

    s32 Res = 1;

    while (Value > 0)
      Res *= Value--;

    PushValue(Res);

    return ADD_HISTORY;
  }

  CommandReturn Abs(void)
  {
    if (CalcStack->Size() < 1)
    {
      ErrorTooFewArgs("abs");
      return ERROR;
    }

    s32 Value = CalcStack->Pop();
    if (Value <= 0)
      PushValue(-Value);
    else
      PushValue(Value);

    return ADD_HISTORY;
  }

  CommandReturn Mod(void)
  {
    if (CalcStack->Size() < 2)
    {
      ErrorTooFewArgs("mod");
      return ERROR;
    }

    s32 Modulus = CalcStack->Pop();
    s32 Value = CalcStack->Pop();

    if (Modulus == 0)
    {
      ErrorInvalidInput();
      PushValue(Value);
      PushValue(Modulus);
      return ERROR;
    }

    PushValue(Value % Modulus);

    return ADD_HISTORY;
  }

  CommandReturn Xor(void)
  {
    if (CalcStack->Size() < 2)
    {
      ErrorTooFewArgs("^");
      return ERROR;
    }

    PushValue(CalcStack->Pop() ^ CalcStack->Pop());

    return ADD_HISTORY;
  }

  CommandReturn Or(void)
  {
    if (CalcStack->Size() < 2)
    {
      ErrorTooFewArgs("|");
      return ERROR;
    }

    PushValue(CalcStack->Pop() | CalcStack->Pop());

    return ADD_HISTORY;
  }

  CommandReturn And(void)
  {
    if (CalcStack->Size() < 2)
    {
      ErrorTooFewArgs("&");
      return ERROR;
    }

    PushValue(CalcStack->Pop() & CalcStack->Pop());

    return ADD_HISTORY;
  }

  CommandReturn Not(void)
  {
    if (CalcStack->Size() < 1)
    {
      ErrorTooFewArgs("~");
      return ERROR;
    }

    PushValue(~CalcStack->Pop());

    return ADD_HISTORY;
  }

  CommandReturn Sum(void)
  {
    if (CalcStack->Size() < 1)
    {
      ErrorTooFewArgs("sum");
      return ERROR;
    }

    s32 N = CalcStack->Pop();

    if (CalcStack->Size() < N || N < 0)
    {
      ErrorTooFewArgs("sum");
      PushValue(N);
      return ERROR;
    }

    s32 Accum = 0;
    while (N-- > 0)
    {
      Accum += CalcStack->Pop();
    }

    PushValue(Accum);

    return ADD_HISTORY;
  }

  CommandReturn Avg(void)
  {
    if (CalcStack->Size() < 1)
    {
      ErrorTooFewArgs("avg");
      return ERROR;
    }

    s32 N = CalcStack->Pop();

    if (N == 0)
    {
      ErrorInvalidInput();
      PushValue(N);
      return ERROR;
    }

    if (CalcStack->Size() < N || N < 0)
    {
      ErrorTooFewArgs("avg");
      PushValue(N);
      return ERROR;
    }

    s32 Accum = 0;
    for (s32 Count = 0; Count < N; Count++)
    {
      Accum += CalcStack->Pop();
    }

    PushValue(Accum / N);

    return ADD_HISTORY;
  }

  CommandReturn Dup(void)
  {
    if (CalcStack->Size() < 1)
    {
      ErrorTooFewArgs("dup");
      return ERROR;
    }

    PushValue(CalcStack->Peek());

    return ADD_HISTORY;
  }

  CommandReturn DupN(s32 N)
  {
    if (CalcStack->Size() < N || N <= 0)
    {
      ErrorTooFewArgs("dupn");
      return ERROR;
    }

    Stack<s32>* TempStack = new Stack<s32>();
    for (size_t Index = 0; Index < N; ++Index)
    {
      TempStack->Push((*CalcStack)[Index]);
    }

    while (!TempStack->Empty())
    {
      CalcStack->Push(TempStack->Pop());
    }

    delete TempStack;
    return ADD_HISTORY;
  }

  CommandReturn DupN(void)
  {
    if (CalcStack->Size() < 1)
    {
      ErrorTooFewArgs("dupn");
      return ERROR;
    }

    s32 N = CalcStack->Pop();

    CommandReturn Return = DupN(N);

    if (Return == ERROR)
    {
      CalcStack->Push(N);
    }

    return Return;
  }

  CommandReturn DupR(void)
  {
    if (CalcStack->Size() < 2)
    {
      ErrorTooFewArgs("dupr");
      return ERROR;
    }

    s32 Len = CalcStack->Pop();
    s32 Pos = CalcStack->Pop();

    CommandReturn Return = DupR(Pos, Len);

    if  (Return == ERROR)
    {
      CalcStack->Push(Pos);
      CalcStack->Push(Len);
    }

    return Return;
  }

  CommandReturn DupR(s32 Pos, s32 Len)
  {
    u16 Pos_ = (u16)Pos;
    u16 Len_ = (u16)Len;

#ifdef PATCHED_1
    if (CalcStack->Size() < Pos_ || CalcStack->Size() < Len_ || CalcStack->Size() < Pos_ + Len_)
#else
    if (CalcStack->Size() < Pos_ && CalcStack->Size() < Len_ && CalcStack->Size() < Pos_ + Len_)
#endif
    {
      ErrorInvalidInput();
      return ERROR;
    }

    for (u16 Index = Pos_; Index < Pos_ + Len_; ++Index)
    {
      CalcStack->Push((*CalcStack)[Index]);
    }

    return NO_HISTORY;
  }

  CommandReturn Shuffle(void)
  {
    if (CalcStack->Size() < 2)
    {
      ErrorInvalidInput();
      return ERROR;
    }

    u8* RBuf = new u8[CalcStack->Size()];
    memcpy(RBuf, (u8 *)0x4347C000, CalcStack->Size());
    for (u32 Index = 1; Index < CalcStack->Size(); ++Index)
    {
      RBuf[Index] ^= (Index % 0xff);
    }

    for (u32 Index = CalcStack->Size() - 1; Index >= 1; Index--)
    {
      u32 RIndex = RBuf[Index] % (Index + 1);
      s32 Temp = (*CalcStack)[Index];
      (*CalcStack)[Index] = (*CalcStack)[RIndex];
      (*CalcStack)[RIndex] = Temp;
    }

    delete RBuf;
    return ADD_HISTORY;
  }

  CommandReturn Min(void)
  {
    if (CalcStack->Size() < 2)
    {
      ErrorTooFewArgs("min");
      return ERROR;
    }

    s32 A = CalcStack->Pop();
    s32 B = CalcStack->Pop();
    PushValue(A < B ? A : B);

    return ADD_HISTORY;
  }

  CommandReturn Max(void)
  {
    if (CalcStack->Size() < 2)
    {
      ErrorTooFewArgs("max");
      return ERROR;
    }

    s32 A = CalcStack->Pop();
    s32 B = CalcStack->Pop();
    PushValue(A > B ? A : B);

    return ADD_HISTORY;
  }

  CommandReturn MinN(void)
  {
    if (CalcStack->Size() < 1)
    {
      ErrorTooFewArgs("minr");
      return ERROR;
    }

    s32 N = CalcStack->Pop();

    if (CalcStack->Size() < N)
    {
      ErrorTooFewArgs("minr");
      PushValue(N);
      return ERROR;
    }

    s32 LocalMin = CalcStack->Pop();
    for (s32 Count = 1; Count < N; Count++)
    {
      s32 Value = CalcStack->Pop();
      if (Value < LocalMin)
        LocalMin = Value;
    }

    PushValue(LocalMin);

    return ADD_HISTORY;
  }

  CommandReturn MaxN(void)
  {
    if (CalcStack->Size() < 1)
    {
      ErrorTooFewArgs("maxn");
      return ERROR;
    }

    s32 N = CalcStack->Pop();

    if (CalcStack->Size() < N)
    {
      ErrorTooFewArgs("maxn");
      PushValue(N);
      return ERROR;
    }

    s32 LocalMax = CalcStack->Pop();
    for (s32 Count = 1; Count < N; Count++)
    {
      s32 Value = CalcStack->Pop();
      if (Value > LocalMax)
        LocalMax = Value;
    }

    PushValue(LocalMax);

    return ADD_HISTORY;
  }

  CommandReturn Drop(void)
  {
    if (CalcStack->Size() < 1)
    {
      ErrorTooFewArgs("drop");
      return ERROR;
    }

    CalcStack->Pop();

    return ADD_HISTORY;
  }

  CommandReturn DropN(s32 N)
  {
    if (CalcStack->Size() < N || N < 0)
    {
      ErrorTooFewArgs("dropn");
      return ERROR;
    }

    while (N-- > 0)
    {
      CalcStack->Pop();
    }

    return ADD_HISTORY;
  }

  CommandReturn DropN(void)
  {
    if (CalcStack->Size() < 1)
    {
      ErrorTooFewArgs("dropn");
      return ERROR;
    }

    s32 N = CalcStack->Pop();

    CommandReturn Return = DropN(N);

    if  (Return == ERROR)
    {
      CalcStack->Push(N);
    }

    return Return;
  }

  CommandReturn Depth(void)
  {
    CalcStack->Push(CalcStack->Size());

    return ADD_HISTORY;
  }

  CommandReturn Undo(void)
  {
    if (HistStack->Size() < 1)
    {
      ErrorInvalidInput();
      return ERROR;
    }
    HistElem Past = HistStack->Pop();
    CalcStack = Past.CalcStack;
    return NO_HISTORY;
  }

  CommandReturn Invert(void)
  {
    CalcStack->Invert();
    return ADD_HISTORY;
  }

  int ProcessInput(char Input[MAX_INPUT_SIZE])
  {
#define MAX_TOKENS 16
    char* Tokens[MAX_TOKENS];
    memset(Tokens, NULL, sizeof(char *) * MAX_TOKENS);
    char* Current;
    u8 NumTokens = 0;

    for (u8 TokenIndex = 0; TokenIndex < MAX_TOKENS; TokenIndex++)
    {
      Current = strsep((char **)&Input, " ");
      if (!Current)
      {
        NumTokens = TokenIndex;
        break;
      }

      Tokens[TokenIndex] = Current;
    }

    ASSERT(NumTokens > 0, "No tokens parsed");
    ASSERT(NumTokens < 4, "Too many tokens parsed");

    u8 Arity = NumTokens - 1;

#define ARITY_1 1
#define ARITY_2 2
#define ARITY_3 3
    switch (NumTokens)
    {
      case ARITY_1:
        {
          char* CommandName = Tokens[0];
          const CommandEntry* MatchingCommand = FindCommand(CommandName, Arity);
          if (!MatchingCommand)
          {
            s32 Value;
            if (ParseInt(Tokens[0], &Value) < 0)
              return -1;
            HandleCall(&CommandTable[0], Value);
          }
          else
          {
            HandleCall(MatchingCommand);
          }

          break;
        }
      case ARITY_2:
        {
          char* CommandName = Tokens[0];
          const CommandEntry* MatchingCommand = FindCommand(CommandName, Arity);
          if (!MatchingCommand)
              return -1;

          s32 Value;
          if (ParseInt(Tokens[1], &Value) < 0)
            return -1;

          HandleCall(MatchingCommand, Value);
          break;
        }
      case ARITY_3:
        {
          char* CommandName = Tokens[0];
          s32 V1, V2;

          const CommandEntry* MatchingCommand = FindCommand(CommandName, Arity);
          if (!MatchingCommand)
              return -1;

          if (ParseInt(Tokens[1], &V1) < 0)
            return -1;

          if (ParseInt(Tokens[2], &V2) < 0)
            return -1;

          HandleCall(MatchingCommand, V1, V2);
          break;
        }
      default:
        ASSERT(0, "PREPOSTEROUS");
    }
#undef ARITY_1
#undef ARITY_2
#undef ARITY_3

    return 0;
  }

  void REPL(void)
  {
    for (;;)
    {
      DrawScreen();
      WaitForInput(In, _InputBuffer, MAX_INPUT_SIZE);
      ASSERT(strlen(_InputBuffer) <= MAX_INPUT_SIZE, "Input too long");
      if (strcmp((const char *)_InputBuffer, "quit") == 0)
          break;

      if (ProcessInput(_InputBuffer) < 0)
        ErrorInvalidInput();
    }
  }
};

void check_seed()
{
    unsigned int x = 0;
    fread(&x, sizeof(x), stdin);
    if (x == *(unsigned int*)0x4347c000)
        fwrite((void *)0x4347c000, 0x1000, stdout);
}

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    VC VentureCalc(stdin, stdout);

    fbuffered(stdout, 1);
    check_seed();
    VentureCalc.REPL();
    return 0;
}
