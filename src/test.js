const db = require('bindings')('DBExport');

const connect = db.CreateMySQLConnect('host=127.0.0.2;port=3306;user=root;pwd=2001;db=personnel;')

const stmt = connect.createStatement('select loginname from personnel.user;')

const result_set = stmt.executeQuery()

while (result_set.next()) {
  const name = result_set.getText(0)
  console.log(name)
}