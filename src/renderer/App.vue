<script setup lang="ts">
import AppHeader from "./components/AppHeader.vue";
import SidePanel from "./components/SidePanel.vue";
import PagePanel from "./components/PagePanel.vue"
import ConnectDialog from "./components/ConnectDialog.vue";
import WelcomePage from "./components/WelcomePage.vue";
import TablePage from "./components/TablePage.vue";
</script>

<template>
  <div id="app-panel">
    <div id="app-side-panel-box">
      <SidePanel ref="side" :click_callback="do_click_tree"/>
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

<script lang="ts">

function show_dialog() {
  // this.$refs.dialog.dialog_visible = true;
  // this.$refs.dialog.disable = false
}

function do_connect() {
  // this.$refs.dialog.disable = true
  // console.log(this.$refs.dialog.conn_info)
}

function do_click_tree() {
  // const node = this.$refs.side.$refs.tree.getCurrentNode()
  // console.log(node)
}

function test() {
}

</script>

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

html, body {
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
