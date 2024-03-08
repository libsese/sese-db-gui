<template>
  <div id="app-header-box">
    <button class="app-window-button" id="close_button">x</button>
    <button class="app-window-button" id="max_button">+</button>
    <button class="app-window-button" id="hide_button">-</button>
  </div>
</template>

<script>
import {defineComponent} from 'vue'

export default defineComponent({
  name: "AppHeader",
  components: {},
  setup() {

  }
})

</script>

<style>
#app-header-box {
  -webkit-app-region: drag;
  display: flex;
  flex-direction: row-reverse;
  height: 30px;
  background: whitesmoke;
}

.app-window-button {
  -webkit-app-region: no-drag;
  width: 50px;
  height: 30px;
  border: none;
}
</style>