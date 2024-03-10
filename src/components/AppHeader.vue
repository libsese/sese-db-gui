<template>
  <div id="app-header-box">
    <button class="app-window-button"
            v-on:mouseenter="on_mouse_enter_close"
            v-on:mouseleave="on_mouse_leave_close"
            v-on:mousedown="on_mouse_down_close"
            :style="{background: closeButtonBackground}"
            v-on:click="on_click_close">
      <img class="app-window-icon" :src=window_close alt="">
    </button>
    <button class="app-window-button"
            v-on:mouseenter="on_mouse_enter_max"
            v-on:mouseleave="on_mouse_leave_max"
            v-on:mousedown="on_mouse_down_max"
            :style="{background: maxButtonBackground}"
            v-on:click="on_click_max">
      <img class="app-window-icon" ref="window_max_button" id="window_max_button" :src=window_max alt=""/>
    </button>
    <button class="app-window-button"
            v-on:mouseenter="on_mouse_enter_min"
            v-on:mouseleave="on_mouse_leave_min"
            v-on:mousedown="on_mouse_down_min"
            :style="{background: hideButtonBackground}"
            v-on:click="on_click_min">
      <img class="app-window-icon" :src=window_min alt="">
    </button>
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
    on_mouse_enter_close() {
      this.closeButtonBackground = '#c42b1c'
    },
    on_mouse_leave_close() {
      this.closeButtonBackground = 'whitesmoke'
    },
    on_mouse_down_close() {
      this.closeButtonBackground = '#b32c1d'
    },
    on_click_close() {
      ipcRenderer.send('window-close')
    },
    on_mouse_enter_max() {
      this.maxButtonBackground = 'lightgray'
    },
    on_mouse_leave_max() {
      this.maxButtonBackground = 'whitesmoke'
    },
    on_mouse_down_max() {
      this.maxButtonBackground = 'gray'
    },
    on_click_max() {
      ipcRenderer.send('window-max')
    },
    on_mouse_enter_min() {
      this.hideButtonBackground = 'lightgray'
    },
    on_mouse_leave_min() {
      this.hideButtonBackground = 'whitesmoke'
    },
    on_mouse_down_min() {
      this.hideButtonBackground = 'gray'
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
#app-header-box {
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
  -webkit-app-region: no-drag;
  width: 50px;
  height: 30px;
  border: none;
}

.app-window-icon {
  width: 20px;
  height: 11px;
}
</style>