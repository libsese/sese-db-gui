<template>
  <div id="app-panel">
    <div id="app-side-panel-box">
      <SidePanel/>
    </div>
    <div id="app-main-panel-box">
      <AppHeader/>
    </div>
  </div>
</template>

<script>
import AppHeader from "@/components/AppHeader.vue";
import SidePanel from "@/components/SidePanel.vue";

export default {
  name: 'App',
  components: {
    SidePanel,
    AppHeader
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
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
  width: 160px;
  height: 100vh;
}

#app-main-panel-box {
  flex: 1;
  display: flex;
  flex-flow: column;
  width: calc(100% - 160px);
  height: 100vh;
}
</style>
