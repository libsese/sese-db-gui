<script setup lang="ts">
import AppHeader from "./components/AppHeader.vue";
import SidePanel from "./components/SidePanel.vue";
import PagePanel from "./components/PagePanel.vue"
import ConnectDialog from "./components/ConnectDialog.vue";
import WelcomePage from "./components/WelcomePage.vue";
import TablePage from "./components/TablePage.vue";
import {ref} from "vue";

const side = ref<any>(null)
const dialog = ref<any>(null)
var info

function convertTreeNode(root: String, strings: String[]): any[] {
  console.log(strings)
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

const click_tree = () => {

}

const show_dialog = () => {
  dialog.value.dialog_visible = true
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
  side.value.data = convertTreeNode(info.user + '@' + info.host, tables)
}

const test = () => {
}

</script>

<template>
  <div id="app-panel">
    <div id="app-side-panel-box">
      <SidePanel ref="side" :click_callback="click_tree"/>
    </div>
    <div id="app-main-panel-box">
      <AppHeader :connect_callback="show_dialog" :test_callback="test"/>
      <PagePanel ref="pages">
        <welcome-page/>
        <TablePage ref="table" header="测试"/>
      </PagePanel>
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
