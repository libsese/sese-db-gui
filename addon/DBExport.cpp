#include <napi.h>

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
        value_ = std::unique_ptr<sese::DateTime>(static_cast<sese::DateTime *>(info.Data()));
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
                INSTANCE_FUNC(getColumns),
                INSTANCE_FUNC(getInteger),
                INSTANCE_FUNC(getLong),
                INSTANCE_FUNC(getString),
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
        result_set_ = std::unique_ptr<sese::db::ResultSet>(static_cast<sese::db::ResultSet *>(info.Data()));
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

    EXPORT_FUNC(getString) {
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
                INSTANCE_FUNC(executeUpdate)
            }
        );
        constructor = Napi::Persistent(func);
        constructor.SuppressDestruct();

        exports.Set("PreparedStatement", func); // NOLINT
        env.SetInstanceData<Napi::FunctionReference>(&constructor);
        return exports;
    }

    explicit PreparedStatement(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    }

    EXPORT_FUNC(executeQuery) {
        auto res = prepared_statement_->executeQuery();
        if (!res) {
            return {};
        }
        auto raw = res.get();
        res.reset();
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
        // auto value = info[1].As<Napi::ObjectWrap<DateTime>>();
        // auto res = prepared_statement_->setDateTime(index, *value);
        // return Napi::Boolean::New(info.Env(), res);
        return {};
    }

    EXPORT_FUNC(getColumnType) {
        auto index = info[0].As<Napi::Number>().Uint32Value();
        auto type = new sese::db::MetadataType();
        auto rt = prepared_statement_->getColumnType(index, *type);
        // todo 导出枚举
        return {};
    }

private:
    std::unique_ptr<sese::db::PreparedStatement> prepared_statement_{};
};

Napi::FunctionReference PreparedStatement::constructor{};

// class Connect final : public Napi::ObjectWrap<Connect> {
// public:
//     static Napi::Object Init(Napi::Env env, Napi::Object exports) {
//         Napi::Function func = DefineClass(
//             env,
//             "Connect",
//             {
//
//             }
//         );
//         return exports;
//     }
//
//     explicit Connect(const Napi::CallbackInfo &info) : ObjectWrap(info) {
//     }
// };

// static Connect CreateMySQLConnect(Napi::CallbackInfo &info) {
// }


Napi::Object Init(Napi::Env env, Napi::Object exports) {
    DateTime::Init(env, exports);
    ResultSet::Init(env, exports);
    PreparedStatement::Init(env, exports);
    return exports;
}

NODE_API_MODULE(DBExport, Init)
