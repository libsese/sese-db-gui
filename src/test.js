const db = require('bindings')('DBExport');

const connect = db.CreateMySQLConnect('host=127.0.0.2;port=3306;user=root;pwd=2001;db=personnel;')

const result_set = connect.executeQuery('select loginname from personnel.user;')

while (result_set.next()) {
  const name = result_set.getText(0)
  console.log(name)
}