#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enQuestionLevel {Easy = 1,  Med = 2, Hard = 3 , Mix = 4};
enum enOpType {Add = 1, Sub = 2 , Mul = 3 , Div = 4 , MixOp = 5};

struct stQuestionInfo {

	short Number1 = 0;
	short Number2 = 0;
	enOpType OpType;
	enQuestionLevel QuestionLevel;
	short CorrectAnswer = 0;
	short PlayerAnswer = 0;
	bool AnswerResult = false;

};

struct stQuizz {

	stQuestionInfo Questions[100];
	short NumberOfQuestions = 0;
	enQuestionLevel QuestionLevel;
	enOpType OpType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool IsPassed = false;

};

short ReadHowManyQuestions() {

	short NumberOfQuestions = 0;
	do {

		cout << "How Many Questions Do You Want To Answer (1-100) ? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions>100);
		
	return NumberOfQuestions;
}

enQuestionLevel ReadQuestionsLevel() {

	short QuestionsLevel = 0;

	do {

		cout << "Enter Questions Level [1] Easy , [2] Med , [3] Hard , [4] Mix ? ";
		cin >> QuestionsLevel;

	} while (QuestionsLevel < 1 || QuestionsLevel > 4);

	return (enQuestionLevel)QuestionsLevel;
}

enOpType ReadOperationType() {

	short OperationType = 0;

	do {

		cout << "Enter OperationType [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix ? ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType > 5);

	return (enOpType)OperationType;
}

short RandomNumber(short from, short to) {
	return rand() % (to - from + 1) + from;
}

short ReadPlayerAnswer() {

	short PlayerAnswer;
	cin >> PlayerAnswer;

	return PlayerAnswer;
}

void SetScreenColor(bool Result) {

	if (Result) {
		system("color 2F");
	}
	else {
		system("color 4F");
		cout << "\a";
	}

}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short NumberOfQuestion) {

	if (Quizz.Questions[NumberOfQuestion].PlayerAnswer != Quizz.Questions[NumberOfQuestion].CorrectAnswer) {

		Quizz.Questions[NumberOfQuestion].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;


		cout << "Wrong Answer :-( " << endl;
		cout << "The Right Answer Is : " << Quizz.Questions[NumberOfQuestion].CorrectAnswer << endl;

	}
	else {

		Quizz.Questions[NumberOfQuestion].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-) \n\n\n";

	}

	SetScreenColor(Quizz.Questions[NumberOfQuestion].AnswerResult);

}

string GetOperationSym(enOpType OpType) {
	string OpSym[4] = { "+" , "-" , "*" , "/" };
	return OpSym[OpType - 1];
}

string GetQuestionLevel(enQuestionLevel Level) {
	string LevelName[4] = { "Easy","Med","Hard","Mix"};
	return LevelName[Level - 1];
}

string GetOpName(enOpType OpType) {
	string OpName[5] = { "Add","Sub","Mul" , "Div", "Mix"};
	return OpName[OpType - 1];
}

short SimpleCalculator(short Number1, short Number2, enOpType OpType) {

    switch(OpType){
	
	case enOpType::Add:
		return Number1 + Number2;
	case enOpType::Sub:
		return Number1 - Number2;
	case enOpType::Mul:
		return Number1 * Number2;
	case enOpType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;

	}

}

stQuestionInfo GenerateQuestion(enQuestionLevel QuestionLevel,enOpType OpType) {

	stQuestionInfo Question;
    
	if (QuestionLevel == enQuestionLevel::Mix) {
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}

	if (OpType == enOpType::MixOp) {
		OpType = (enOpType)RandomNumber(1, 4);
	}

	Question.OpType = OpType;
	Question.QuestionLevel = QuestionLevel;

	switch (Question.QuestionLevel) {

	case enQuestionLevel::Easy:

		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1,Question.Number2,Question.OpType);
		return Question;
	case enQuestionLevel::Med:

		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1,Question.Number2,Question.OpType);
		return Question;
	case enQuestionLevel::Hard:

		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1,Question.Number2,Question.OpType);
		return Question;
	}

}

void GenerateQuestions(stQuizz& Quizz) {

	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++) {
		Quizz.Questions[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
	}

}

void PrintQuestion(stQuizz Quizz , short QuestionNumber) {

	cout << "\nQuestion [" << QuestionNumber << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.Questions[QuestionNumber].Number1 << endl;
	cout << Quizz.Questions[QuestionNumber].Number2 << " " << GetOperationSym(Quizz.OpType) << endl ;
	cout << "----------\n";

}

void AskAndCrrectQuestionListAnswers(stQuizz& Quizz) {


	for (short QuestionsNumber = 0; QuestionsNumber < Quizz.NumberOfQuestions; QuestionsNumber++) {

		PrintQuestion(Quizz,QuestionsNumber);
		Quizz.Questions[QuestionsNumber].PlayerAnswer = ReadPlayerAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionsNumber);

	}

	Quizz.IsPassed = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);

}

string IsPassed(bool Result) {

	if (Result)
		return "Pass :-) ";
	else
		return "Fail :-( ";

}

void PrintFinalResults(stQuizz Quizz) {

	cout << "----------------------------------\n\n";
	cout << "Final Results Is " << IsPassed(Quizz.IsPassed) << endl << endl;
	cout << "----------------------------------\n\n";
	cout << "Number of questions     : " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level         : " << GetQuestionLevel(Quizz.QuestionLevel) << endl;
	cout << "OpType                  : " << GetOpName(Quizz.OpType) << endl;
	cout << "Number of Right Answers : " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers : " << Quizz.NumberOfWrongAnswers << endl << endl;
	cout << "----------------------------------\n\n";

}

void PlayMathGame() {

	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOperationType();

	GenerateQuestions(Quizz);
	AskAndCrrectQuestionListAnswers(Quizz);
	
	PrintFinalResults(Quizz);

}

void ResetScreen() {

	system("cls");
	system("color 0F");

}

void StartGame() {

	char IsContinue = 'y';

	do {

		ResetScreen();
		PlayMathGame();

		cout << "Do You Want To Play Again ? Y/N ? ";
		cin >> IsContinue;

	} while (IsContinue == 'y' || IsContinue == 'Y');

}

int main() {

	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}