declare module 'typings/db' {
  export function CreateMySQLConnect(connect_string: string): Connect

  export interface Datetime {
    getYears(): Number

    getMonths(): Number

    getDays(): Number

    getMinutes(): Number

    getSeconds(): Number

    getMilliseconds(): Number

    getMicroseconds(): Number

    getUTC(): Number

    getDayOfWeek(): Number

    getDayOfYear(): Number

    getTimestamp(): Number
  }

  export interface ResultSet {
    reset(): Boolean

    next(): Boolean

    getText(index: Number): string

    getColumns(): Number

    getInteger(index: Number): Number

    getLong(index: Number): Number

    getDouble(index: Number): Number

    getFloat(index: Number): Number

    getDateTime(index: Number): Datetime

    isNull(index: Number): Boolean
  }

  export interface Metadata {
    Text: Number
    Boolean: Number
    Char: Number
    Short: Number
    Integer: Number
    Long: Number
    Float: Number
    Double: Number
    Date: Number
    Time: Number
    DateTime: Number
    Unknown: Number
  }

  export interface PreparedStatement {
    executeQuery(): ResultSet

    executeUpdate(): Number

    setDouble(index: Number, value: Number): Boolean

    setFloat(index: Number, value: Number): Boolean

    setInteger(index: Number, value: Number): Boolean

    setLong(index: Number, value: Number): Boolean

    setText(index: Number, value: string): Boolean

    setNull(index: Number): Boolean

    setDateTime(index: Number, value: Datetime): Boolean

    getColumnType(index: Number): Metadata
  }

  export interface Connect {
    executeQuery(sql: string): ResultSet

    executeUpdate(sql: string): Number

    createStatement(sql: string): PreparedStatement

    getLastError(): Number

    getLastErrorMessage(): string

    setAutoCommit(enable: Boolean): Boolean

    rollback(): Boolean

    begin(): Boolean

    commit(): Boolean

    getInsertId(): Number
  }
}