<script setup lang="ts">
import AppHeader from "./components/AppHeader.vue";
import SidePanel from "./components/SidePanel.vue";
import PagePanel from "./components/PagePanel.vue"
import ConnectDialog, {ConnInfo} from "./components/ConnectDialog.vue";
import {TableColumn} from "./components/TablePage.vue";
import {ref} from "vue";

const header = ref<any>(null);
const side = ref<any>(null);
const dialog = ref<any>(null);
const pages = ref<any>(null);

let info: ConnInfo;
let conn_status: boolean = false;

function convert_tree_node(root: String, strings: String[]): any[] {
  const result: any[] = [];
  const firstObject = {
    id: 1,
    label: root,
    children: [] as any[]
  }

  for (let i = 1; i < strings.length; i++) {
    const childObject = {
      id: i + 1,
      label: strings[i],
      children: []
    };
    firstObject.children.push(childObject);
  }

  result.push(firstObject);
  return result;
}

function convert_table_header(headers: String[]): any[] {
  const result: any[] = [];
  for (let i = 0; i < headers.length; i++) {
    const column: TableColumn = {
      prop: headers[i].toString(),
      label: headers[i].toString()
    }
    result.push(column);
  }
  console.log(result)
  return result;
}

function convert_table_content(headers: string[], contents: string[]): any[] {
  const result: any[] = [];
  const rows = contents.length / headers.length;
  for (let i = 0; i < rows; i++) {
    const row: { [key: string]: string } = {}
    for (let n = 0; n < headers.length; n++) {
      const key = headers[n];
      const value = contents[i * headers.length + n];
      row[key] = value;
    }
    console.log(row);
    result.push(row);
  }
  return result;
}

const on_selected = async (item: any) => {
  if (item && conn_status) {
    const headers = await window.electronAPI.get_table_headers(info.db, item.label)
    const contents = await window.electronAPI.get_table_contents(headers, item.label)
    pages.value.add_tab({
      title: item.label + " 预览",
      component_name: "TablePage",
      columns: convert_table_header(headers),
      data: convert_table_content(headers, contents)
    })
  }
}

const show_dialog = () => {
  if (conn_status) {
    side.value.data = [{label: "尚未连接"}]
    header.value.connect_text = '+';
    header.value.connect_type = 'primary';
    conn_status = false;
  } else {
    dialog.value.dialog_visible = true
  }
}

const do_connect = async () => {
  info = dialog.value.conn_info
  if (!info.host ||
    !info.port ||
    !info.db ||
    !info.user ||
    !info.pwd
  ) {
    dialog.value.message = '缺少必要字段';
    return;
  }
  window.electronAPI.open_db(info.host, parseInt(info.port), info.db, info.user, info.pwd);
  const tables = await window.electronAPI.get_tables(info.db);
  dialog.value.message = '';
  dialog.value.dialog_visible = false;

  // 构建树节点
  side.value.data = convert_tree_node(info.user + '@' + info.host, tables);

  header.value.connect_text = '-';
  header.value.connect_type = 'danger';

  conn_status = true;
}

</script>

<template>
  <div id="app-panel">
    <div id="app-side-panel-box">
      <SidePanel ref="side" :on_selected="on_selected"/>
    </div>
    <div id="app-main-panel-box">
      <AppHeader ref="header" :connect_callback="show_dialog"/>
      <PagePanel ref="pages"/>
      <ConnectDialog ref="dialog" :callback="do_connect"/>
    </div>
  </div>
</template>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  -ms-user-select: none;
  user-select: none;
  text-align: center;
  color: #2c3e50;
  overflow: hidden;
}

html,
body {
  width: 100%;
  height: 100%;
  margin: 0;
  padding: 0;
  overflow: hidden;
}

#app-panel {
  display: flex;
  flex-direction: row;
  width: 100%;
  height: 100%;
}

#app-side-panel-box {
  width: 180px;
  height: 100vh;
}

#app-main-panel-box {
  flex: 1;
  display: flex;
  flex-flow: column;
  width: calc(100% - 180px);
  height: 100vh;
}
</style>
