#include <napi.h>

#define ENABLE_RETURN_CLASS

#include <sese/db/DriverManager.h>

#define EXPORT_FUNC(name) Napi::Value name(const Napi::CallbackInfo &info)
#define INSTANCE_FUNC(name) InstanceMethod(#name, &DateTime::name)

// ReSharper disable CppMemberFunctionMayBeConst

class DateTime final : public Napi::ObjectWrap<DateTime> {
public:
    static Napi::FunctionReference constructor;

    static Napi::Object Init(Napi::Env env, Napi::Object exports) {
        Napi::Function func = DefineClass(
                env,
                "DateTime",
                {
                        INSTANCE_FUNC(getYears),
                        INSTANCE_FUNC(getMonths),
                        INSTANCE_FUNC(getDays),
                        INSTANCE_FUNC(getMinutes),
                        INSTANCE_FUNC(getSeconds),
                        INSTANCE_FUNC(getMilliseconds),
                        INSTANCE_FUNC(getMicroseconds),
                        INSTANCE_FUNC(getUTC),
                        INSTANCE_FUNC(getDayOfWeek),
                        INSTANCE_FUNC(getDayOfYear),
                        INSTANCE_FUNC(getTimestamp)
                }
        );
        constructor = Napi::Persistent(func);
        constructor.SuppressDestruct();

        exports.Set("DateTime", func); // NOLINT
        env.SetInstanceData<Napi::FunctionReference>(&constructor);
        return exports;
    }

    explicit DateTime(const Napi::CallbackInfo &info) : ObjectWrap(info) {
        if (info.Length() != 1) {
            Napi::Error::New(info.Env(), "failed to construct DateTime").ThrowAsJavaScriptException();
            return;
        }
        if (info[0].IsExternal()) {
            value_ = std::unique_ptr<sese::DateTime>(info[0].As<Napi::External<sese::DateTime>>().Data());
        } else if (info[0].IsNumber()) {
            auto timestamp = info[0].As<Napi::Number>().Int64Value() * 1000 * 1000;
            value_ = std::make_unique<sese::DateTime>(timestamp, 0);
        } else {
            Napi::Error::New(info.Env(), "failed to construct DateTime").ThrowAsJavaScriptException();
        }
    }

    EXPORT_FUNC(getYears) {
        return Napi::Number::New(info.Env(), value_->getYears());
    }

    EXPORT_FUNC(getMonths) {
        return Napi::Number::New(info.Env(), value_->getMonths());
    }

    EXPORT_FUNC(getDays) {
        return Napi::Number::New(info.Env(), value_->getDays());
    }

    EXPORT_FUNC(getMinutes) {
        return Napi::Number::New(info.Env(), value_->getMinutes());
    }

    EXPORT_FUNC(getSeconds) {
        return Napi::Number::New(info.Env(), value_->getSeconds());
    }

    EXPORT_FUNC(getMilliseconds) {
        return Napi::Number::New(info.Env(), value_->getMilliseconds());
    }

    EXPORT_FUNC(getMicroseconds) {
        return Napi::Number::New(info.Env(), value_->getMicroseconds());
    }

    EXPORT_FUNC(getUTC) {
        return Napi::Number::New(info.Env(), value_->getUTC());
    }

    EXPORT_FUNC(getDayOfWeek) {
        return Napi::Number::New(info.Env(), value_->getDayOfWeek());
    }

    EXPORT_FUNC(getDayOfYear) {
        return Napi::Number::New(info.Env(), value_->getDayOfYear());
    }

    EXPORT_FUNC(getTimestamp) {
        return Napi::Number::New(info.Env(), static_cast<double>(value_->getTimestamp()));
    }

    [[nodiscard]] auto getValue() const {
        return value_.get();
    }

private:
    std::unique_ptr<sese::DateTime> value_{};
};

Napi::FunctionReference DateTime::constructor;

#undef INSTANCE_FUNC

#define INSTANCE_FUNC(name) InstanceMethod(#name, &ResultSet::name)

class ResultSet final : public Napi::ObjectWrap<ResultSet> {
public:
    static Napi::FunctionReference constructor;

    static Napi::Value Init(Napi::Env env, Napi::Object exports) {
        Napi::Function func = DefineClass(
                env,
                "ResultSet",
                {
                        INSTANCE_FUNC(reset),
                        INSTANCE_FUNC(next),
                        INSTANCE_FUNC(getText),
                        INSTANCE_FUNC(getColumns),
                        INSTANCE_FUNC(getInteger),
                        INSTANCE_FUNC(getLong),
                        INSTANCE_FUNC(getDouble),
                        INSTANCE_FUNC(getFloat),
                        INSTANCE_FUNC(getDateTime),
                        INSTANCE_FUNC(isNull)
                }
        );
        constructor = Napi::Persistent(func);
        constructor.SuppressDestruct();

        exports.Set("ResultSet", func); // NOLINT
        env.SetInstanceData<Napi::FunctionReference>(&constructor);
        return exports;
    }

    explicit ResultSet(const Napi::CallbackInfo &info) : ObjectWrap(info) {
        auto raw = info[0].As<Napi::External<sese::db::ResultSet>>();
        this->result_set_ = std::unique_ptr<sese::db::ResultSet>(raw.Data());
    }

    EXPORT_FUNC(reset) {
        result_set_->reset();
        return {};
    }

    EXPORT_FUNC(next) {
        auto res = result_set_->next();
        return Napi::Boolean::New(info.Env(), res);
    }

    EXPORT_FUNC(getColumns) {
        auto res = result_set_->getColumns();
        return Napi::Number::New(info.Env(), static_cast<double>(res));
    }

    EXPORT_FUNC(getInteger) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto res = result_set_->getInteger(index);
        return Napi::Number::New(info.Env(), res);
    }

    EXPORT_FUNC(getLong) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto res = result_set_->getLong(index);
        return Napi::Number::New(info.Env(), static_cast<double>(res));
    }

    EXPORT_FUNC(getText) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto res = result_set_->getString(index);
        return Napi::String::New(info.Env(), res.data());
    }

    EXPORT_FUNC(getDouble) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto res = result_set_->getDouble(index);
        return Napi::Number::New(info.Env(), res);
    }

    EXPORT_FUNC(getFloat) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto res = result_set_->getFloat(index);
        return Napi::Number::New(info.Env(), res);
    }

    EXPORT_FUNC(getDateTime) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto res = result_set_->getDateTime(index);
        if (!res.has_value()) {
            return {};
        }
        auto datetime = new sese::DateTime(res.value());
        return DateTime::constructor.New({Napi::External<sese::DateTime>::New(info.Env(), datetime)});
    }

    EXPORT_FUNC(isNull) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto res = result_set_->isNull(index);
        return Napi::Boolean::New(info.Env(), res);
    }

private:
    std::unique_ptr<sese::db::ResultSet> result_set_;
};

Napi::FunctionReference ResultSet::constructor{};

#undef INSTANCE_FUNC

class Metadata final : public Napi::ObjectWrap<Metadata> {
public:
    explicit Metadata(const Napi::CallbackInfo &info) : ObjectWrap(info) {}

    static Napi::Object Init(Napi::Env env, Napi::Object exports) {
        Napi::Function func = DefineClass(
                env,
                "Metadata",
                {
                        StaticValue("Text", Napi::Number::New(env, text_)),
                        StaticValue("Boolean", Napi::Number::New(env, boolean_)),
                        StaticValue("Char", Napi::Number::New(env, char_)),
                        StaticValue("Short", Napi::Number::New(env, short_)),
                        StaticValue("Integer", Napi::Number::New(env, integer_)),
                        StaticValue("Long", Napi::Number::New(env, long_)),
                        StaticValue("Float", Napi::Number::New(env, float_)),
                        StaticValue("Double", Napi::Number::New(env, double_)),
                        StaticValue("Date", Napi::Number::New(env, date_)),
                        StaticValue("Time", Napi::Number::New(env, time_)),
                        StaticValue("DateTime", Napi::Number::New(env, dateTime_)),
                        StaticValue("Unknown", Napi::Number::New(env, unknown_))
                }
        );
        exports.Set("Metadata", func); // NOLINT
        return exports;
    }

private:
    static int text_;
    static int boolean_;
    static int char_;
    static int short_;
    static int integer_;
    static int long_;
    static int float_;
    static int double_;
    static int date_;
    static int time_;
    static int dateTime_;
    static int unknown_;
};

int Metadata::text_ = static_cast<int>(sese::db::MetadataType::TEXT);
int Metadata::boolean_ = static_cast<int>(sese::db::MetadataType::BOOLEAN);
int Metadata::char_ = static_cast<int>(sese::db::MetadataType::CHAR);
int Metadata::short_ = static_cast<int>(sese::db::MetadataType::SHORT);
int Metadata::integer_ = static_cast<int>(sese::db::MetadataType::INTEGER);
int Metadata::long_ = static_cast<int>(sese::db::MetadataType::LONG);
int Metadata::float_ = static_cast<int>(sese::db::MetadataType::FLOAT);
int Metadata::double_ = static_cast<int>(sese::db::MetadataType::DOUBLE);
int Metadata::date_ = static_cast<int>(sese::db::MetadataType::DATE);
int Metadata::time_ = static_cast<int>(sese::db::MetadataType::TIME);
int Metadata::dateTime_ = static_cast<int>(sese::db::MetadataType::DATE_TIME);
int Metadata::unknown_ = static_cast<int>(sese::db::MetadataType::UNKNOWN);

#define INSTANCE_FUNC(name) InstanceMethod(#name, &PreparedStatement::name)

class PreparedStatement final : public Napi::ObjectWrap<PreparedStatement> {
public:
    static Napi::FunctionReference constructor;

    static Napi::Object Init(Napi::Env env, Napi::Object exports) {
        Napi::Function func = DefineClass(
                env,
                "PreparedStatement",
                {
                        INSTANCE_FUNC(executeQuery),
                        INSTANCE_FUNC(executeUpdate),
                        INSTANCE_FUNC(setDouble),
                        INSTANCE_FUNC(setFloat),
                        INSTANCE_FUNC(setInteger),
                        INSTANCE_FUNC(setLong),
                        INSTANCE_FUNC(setText),
                        INSTANCE_FUNC(setNull),
                        INSTANCE_FUNC(setDateTime),
                        INSTANCE_FUNC(getColumnType)
                }
        );
        constructor = Napi::Persistent(func);
        constructor.SuppressDestruct();

        exports.Set("PreparedStatement", func); // NOLINT
        env.SetInstanceData<Napi::FunctionReference>(&constructor);
        return exports;
    }

    explicit PreparedStatement(const Napi::CallbackInfo &info) : ObjectWrap(info) {
        auto raw = info[0].As<Napi::External<sese::db::PreparedStatement>>();
        this->prepared_statement_ = std::unique_ptr<sese::db::PreparedStatement>(raw.Data());
    }

    EXPORT_FUNC(executeQuery) {
        auto res = prepared_statement_->executeQuery();
        if (!res) {
            return {};
        }
        auto raw = res.release();
        return ResultSet::constructor.New({Napi::External<sese::db::ResultSet>::New(info.Env(), raw)});
    }

    EXPORT_FUNC(executeUpdate) {
        auto res = prepared_statement_->executeUpdate();
        return Napi::Number::New(info.Env(), static_cast<double>(res));
    }

    EXPORT_FUNC(setDouble) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto value = info[1].As<Napi::Number>().DoubleValue();
        auto res = prepared_statement_->setDouble(index, value);
        return Napi::Boolean::New(info.Env(), res);
    }

    EXPORT_FUNC(setFloat) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto value = info[1].As<Napi::Number>().FloatValue();
        auto res = prepared_statement_->setFloat(index, value);
        return Napi::Boolean::New(info.Env(), res);
    }

    EXPORT_FUNC(setInteger) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto value = info[1].As<Napi::Number>().Int32Value();
        auto res = prepared_statement_->setInteger(index, value);
        return Napi::Boolean::New(info.Env(), res);
    }

    EXPORT_FUNC(setLong) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto value = info[1].As<Napi::Number>().Int64Value();
        auto res = prepared_statement_->setLong(index, value);
        return Napi::Boolean::New(info.Env(), res);
    }

    EXPORT_FUNC(setText) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto value = info[1].As<Napi::String>().Utf8Value();
        auto res = prepared_statement_->setText(index, value.c_str());
        return Napi::Boolean::New(info.Env(), res);
    }

    EXPORT_FUNC(setNull) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto res = prepared_statement_->setNull(index);
        return Napi::Boolean::New(info.Env(), res);
    }

    EXPORT_FUNC(setDateTime) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto datetime = DateTime::Unwrap(info[1].As<Napi::Object>());
        auto res = prepared_statement_->setDateTime(index, *datetime->getValue());
        return Napi::Boolean::New(info.Env(), res);
    }

    EXPORT_FUNC(getColumnType) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        sese::db::MetadataType data;
        auto rt = prepared_statement_->getColumnType(index, data);
        if (!rt) {
            return {};
        }
        return Napi::Number::New(info.Env(), static_cast<int>(data));
    }

private:
    std::unique_ptr<sese::db::PreparedStatement> prepared_statement_{};
};

Napi::FunctionReference PreparedStatement::constructor{};

#undef INSTANCE_FUNC

#define INSTANCE_FUNC(name) InstanceMethod(#name, &Connect::name)

class Connect final : public Napi::ObjectWrap<Connect> {
public:
    static Napi::FunctionReference constructor;

    static Napi::Object Init(Napi::Env env, Napi::Object exports) {
        Napi::Function func = DefineClass(
                env,
                "Connect",
                {
                        INSTANCE_FUNC(executeQuery),
                        INSTANCE_FUNC(executeUpdate),
                        INSTANCE_FUNC(createStatement),
                        INSTANCE_FUNC(getLastError),
                        INSTANCE_FUNC(getLastErrorMessage),
                        INSTANCE_FUNC(setAutoCommit),
                        INSTANCE_FUNC(rollback),
                        INSTANCE_FUNC(begin),
                        INSTANCE_FUNC(commit),
                        INSTANCE_FUNC(getInsertId)
                }
        );
        constructor = Napi::Persistent(func);
        constructor.SuppressDestruct();
        env.SetInstanceData<Napi::FunctionReference>(&constructor);

        exports.Set("Connect", func); // NOLINT
        return exports;
    }

    explicit Connect(const Napi::CallbackInfo &info) : ObjectWrap(info) {
        auto raw = info[0].As<Napi::External<sese::db::DriverInstance>>();
        this->instance_ = std::unique_ptr<sese::db::DriverInstance>(raw.Data());
    }

    EXPORT_FUNC(executeQuery) {
        auto sql = info[0].As<Napi::String>().Utf8Value();
        auto result = this->instance_->executeQuery(sql.c_str());
        if (!result) {
            return {};
        }

        auto raw = result.release();
        return ResultSet::constructor.New({Napi::External<sese::db::ResultSet>::New(info.Env(), raw)});
    }

    EXPORT_FUNC(executeUpdate) {
        auto sql = info[0].As<Napi::String>().Utf8Value();
        auto result = this->instance_->executeUpdate(sql.c_str());
        return Napi::Number::New(info.Env(), static_cast<double>(result));
    }

    EXPORT_FUNC(createStatement) {
        auto sql = info[0].As<Napi::String>().Utf8Value();
        auto result = this->instance_->createStatement(sql.c_str());
        if (!result) {
            return {};
        }

        auto raw = result.release();
        return PreparedStatement::constructor.New({Napi::External<sese::db::PreparedStatement>::New(info.Env(), raw)});
    }

    EXPORT_FUNC(getLastError) {
        auto result = this->instance_->getLastError();
        return Napi::Number::New(info.Env(), static_cast<double>(result));
    }

    EXPORT_FUNC(getLastErrorMessage) {
        auto result = this->instance_->getLastErrorMessage();
        return Napi::String::New(info.Env(), result);
    }

    EXPORT_FUNC(setAutoCommit) {
        auto enable = info[0].As<Napi::Boolean>();
        auto result = this->instance_->setAutoCommit(enable);
        return Napi::Boolean::New(info.Env(), result);
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-result"

    EXPORT_FUNC(getAutoCommit) {
        bool status;
        this->instance_->getAutoCommit(status);
        return Napi::Boolean::New(info.Env(), status);
    }

#pragma clang diagnostic pop

    EXPORT_FUNC(rollback) {
        auto result = this->instance_->rollback();
        return Napi::Boolean::New(info.Env(), result);
    }

    EXPORT_FUNC(commit) {
        auto result = this->instance_->commit();
        return Napi::Boolean::New(info.Env(), result);
    }

    EXPORT_FUNC(begin) {
        auto result = this->instance_->begin();
        return Napi::Boolean::New(info.Env(), result);
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-result"

    EXPORT_FUNC(getInsertId) {
        int64_t id;
        this->instance_->getInsertId(id);
        return Napi::Number::New(info.Env(), static_cast<double>(id));
    }

#pragma clang diagnostic pop

private:
    std::unique_ptr<sese::db::DriverInstance> instance_{};
};

Napi::FunctionReference Connect::constructor{};

Napi::Value CreateMySQLConnect(const Napi::CallbackInfo &info) {
    auto string = info[0].As<Napi::String>().Utf8Value();
    auto instance = sese::db::DriverManager::getInstance(sese::db::DatabaseType::MY_SQL, string.c_str());
    if (!instance) {
        Napi::Error::New(info.Env(),
                         "failed to call sese::db::DriverManager::getInstance").ThrowAsJavaScriptException();
        return {};
    }

    if (instance->getLastError()) {
        Napi::Error::New(info.Env(), instance->getLastErrorMessage()).ThrowAsJavaScriptException();
        return {};
    }

    auto raw = instance.release();
    return Connect::constructor.New({Napi::External<sese::db::DriverInstance>::New(info.Env(), raw)});
}

Napi::Value Add(const Napi::CallbackInfo &info) {
    auto rv = info[0].As<Napi::Number>().Int64Value();
    auto lv = info[1].As<Napi::Number>().Int64Value();
    return Napi::Number::New(info.Env(), static_cast<double>(rv + lv));
}

#include <sese/util/Initializer.h>

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // sese::initCore(0, nullptr);

    DateTime::Init(env, exports);
    ResultSet::Init(env, exports);
    PreparedStatement::Init(env, exports);
    Connect::Init(env, exports);
    Metadata::Init(env, exports);

    exports.Set("CreateMySQLConnect", Napi::Function::New(env, &CreateMySQLConnect));
    exports.Set("Add", Napi::Function::New(env, &Add));

    return exports;
}

NODE_API_MODULE(DBExport, Init)
