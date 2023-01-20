#ifndef OPERATION_RESULT_H
#define OPERATION_RESULT_H

#include <string>
#include <ostream>
#include <memory>
#include <concepts>

namespace mep {

	class OperationResult;

	template<typename T>
	concept StringType = std::convertible_to<T, std::string>;

	template<typename T>
	concept OperationResultType = std::convertible_to<T, OperationResult>;

	class OperationResult {
	public:
		OperationResult() = delete;
		OperationResult(const OperationResult&) = default;
		OperationResult& operator=(const OperationResult&) = default;
		OperationResult(OperationResult&&) = default;
		OperationResult& operator=(OperationResult&&) = default;

		static OperationResult Fail() {
			return OperationResult(ResultType::FAIL);
		}

		template<StringType Message>
		static OperationResult Fail(Message&& message) {
			return OperationResult(ResultType::FAIL, std::forward<Message>(message));
		}

		template<OperationResultType SubResult>
		static OperationResult Fail(SubResult&& subResult) {
			return OperationResult(ResultType::FAIL, std::forward<SubResult>(subResult));
		}

		template<StringType Message, OperationResultType SubResult>
		static OperationResult Fail(Message&& message, SubResult&& subResult) {
			return OperationResult(ResultType::FAIL, std::forward<Message>(message), std::forward<SubResult>(subResult));
		}

		static OperationResult Success() {
			return OperationResult(ResultType::SUCCESS);
		}

		template<StringType Message>
		static OperationResult Success(Message&& message) {
			return OperationResult(ResultType::SUCCESS, std::forward<Message>(message));
		}

		template<OperationResultType SubResult>
		static OperationResult Success(SubResult&& subResult) {
			return OperationResult(ResultType::SUCCESS, std::forward<SubResult>(subResult));
		}

		template<StringType Message, OperationResultType SubResult>
		static OperationResult Success(Message&& message, SubResult&& subResult) {
			return OperationResult(ResultType::SUCCESS, std::forward<Message>(message), std::forward<SubResult>(subResult));
		}

		explicit operator bool() const {
			return _resultType == ResultType::SUCCESS;
		}

		template<StringType Message>
		OperationResult& operator<<(Message&& message) {
			_message.append(std::forward<Message>(message));
			return *this;
		}

	private:
		enum class ResultType {
			FAIL,
			SUCCESS
		};

		explicit OperationResult(ResultType resultType)
				: _resultType(resultType) {

		}

		template<StringType Message>
		explicit OperationResult(ResultType resultType, Message&& message)
				: _resultType(resultType),
				  _message(std::forward<Message>(message)) {

		}

		template<OperationResultType SubResult>
		explicit OperationResult(ResultType resultType, SubResult&& subResult)
				: _resultType(resultType),
				  _subResult(new OperationResult(std::forward<SubResult>(subResult))) {

		}

		template<StringType Message, OperationResultType SubResult>
		explicit OperationResult(ResultType resultType, Message&& message, SubResult&& subResult)
				: _resultType(resultType),
				  _message(std::forward<Message>(message)),
				  _subResult(new OperationResult(std::forward<SubResult>(subResult))) {

		}

		friend std::ostream& operator<<(std::ostream& stream, const OperationResult& operationResult);

		ResultType _resultType;
		std::string _message;
		std::shared_ptr<OperationResult> _subResult;
	};

	std::ostream& operator<<(std::ostream& stream, const OperationResult& operationResult) {
		stream << operationResult._message;
		if (operationResult._subResult != nullptr) {
			stream << (operationResult._subResult->_message.empty() ? "" : " <- ");
			stream << *operationResult._subResult;
		}
		return stream;
	}

}

#endif // !OPERATION_RESULT_H
