<template>
  <div class="app-header-box">
    <div class="app-window-close-button" v-on:click="on_click_close">
      <img class="app-window-icon" :src=window_close alt="">
    </div>
    <div class="app-window-button" v-on:click="on_click_max">
      <img class="app-window-icon" ref="window_max_button" :src=window_max alt=""/>
    </div>
    <div class="app-window-button" v-on:click="on_click_min">
      <img class="app-window-icon" :src=window_min alt="">
    </div>
  </div>
</template>

<script>
import {defineComponent} from 'vue'
import {ipcRenderer} from 'electron'
import window_close from '@/assets/window-close.svg'
import window_max from '@/assets/window-max.svg'
import window_min from '@/assets/window-min.svg'
import window_unmax from '@/assets/window-unmax.svg'

export default defineComponent({
  name: "AppHeader",
  components: {},
  setup() {
    return {
      window_close,
      window_max,
      window_min,
      window_unmax
    }
  },
  data: function () {
    return {
      closeButtonBackground: 'whitesmoke',
      maxButtonBackground: 'whitesmoke',
      hideButtonBackground: 'whitesmoke',
    };
  },
  methods: {
    on_click_close() {
      ipcRenderer.send('window-close')
    },
    on_click_max() {
      ipcRenderer.send('window-max')
    },
    on_click_min() {
      ipcRenderer.send('window-min')
    }
  }
})

ipcRenderer.on('on-maximize', () => {
  document.getElementById('window_max_button').src = window_unmax
})

ipcRenderer.on('on-unmaximize', () => {
  document.getElementById('window_max_button').src = window_max
})
</script>

<style>
.app-header-box {
  -webkit-app-region: drag;
  display: flex;
  flex-direction: row-reverse;
  height: 30px;
  background: whitesmoke;
}

.app-window-button {
  display: flex;
  justify-content: center;
  align-items: center;
  width: 50px;
  height: 100%;
  border: none;
}

.app-window-button:hover {
  background-color: gainsboro;
}

.app-window-button:active {
  background-color: lightgray;
}

.app-window-icon {
  width: 20px;
  height: 11px;
  -webkit-user-select: none;
  -webkit-user-drag: none;
  -webkit-app-region: no-drag;
  cursor: default;
}

.app-window-button, .app-window-close-button {
  display: flex;
  justify-content: center;
  align-items: center;
  width: 50px;
  height: 100%;
}

.app-window-close-button:hover {
  background-color: red;
}

.app-window-close-button:active {
  background-color: #c42b1c;
}

.app-window-close-button {
  background-color: whitesmoke;
}

</style>