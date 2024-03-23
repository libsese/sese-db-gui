<script setup lang="ts">
import AppHeader from "./components/AppHeader.vue";
import SidePanel from "./components/SidePanel.vue";
import PagePanel from "./components/PagePanel.vue"
import ConnectDialog from "./components/ConnectDialog.vue";
import WelcomePage from "./components/WelcomePage.vue";
import TablePage from "./components/TablePage.vue";
import { ref } from "vue";

const dialog = ref<any>(null)

const click_tree = () => {

}

const show_dialog = () => {
  dialog.value.dialog_visible = true
}

const do_connect = () => {
  const info = dialog.value.conn_info
  window.electronAPI.open_db(info.host, parseInt(info.port), info.db, info.user, info.pwd)
}

const test = () => {
}

</script>

<template>
  <div id="app-panel">
    <div id="app-side-panel-box">
      <SidePanel ref="side" :click_callback="click_tree" />
    </div>
    <div id="app-main-panel-box">
      <AppHeader :connect_callback="show_dialog" :test_callback="test" />
      <PagePanel ref="pages">
        <welcome-page />
        <TablePage ref="table" header="测试" />
      </PagePanel>
      <ConnectDialog ref="dialog" :callback="do_connect" />
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
