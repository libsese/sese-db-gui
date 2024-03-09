<template>
  <div id="app-header-box">
    <button class="app-window-button"
            v-on:mouseenter="on_mouse_enter_close"
            v-on:mouseleave="on_mouse_leave_close"
            :style="{background: closeButtonBackground}"
            v-on:click="on_click_close">
      <img class="app-window-icon" :src=window_close alt="">
    </button>
    <button class="app-window-button"
            v-on:mouseenter="on_mouse_enter_max"
            v-on:mouseleave="on_mouse_leave_max"
            :style="{background: maxButtonBackground}"
            v-on:click="on_click_max">
      <img class="app-window-icon" ref="window_max_button" :src=window_max alt=""/>
    </button>
    <button class="app-window-button"
            v-on:mouseenter="on_mouse_enter_min"
            v-on:mouseleave="on_mouse_leave_min"
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
      this.closeButtonBackground = 'indianred'
    },
    on_mouse_leave_close() {
      this.closeButtonBackground = 'whitesmoke'
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
    async on_click_max() {
      const isMax = await ipcRenderer.invoke('window-max')
      if (isMax) {
        this.$refs.window_max_button.src = window_unmax
      } else {
        this.$refs.window_max_button.src = window_max
      }
    },
    on_mouse_enter_min() {
      this.hideButtonBackground = 'lightgray'
    },
    on_mouse_leave_min() {
      this.hideButtonBackground = 'whitesmoke'
    },
    on_click_min() {
      ipcRenderer.send('window-min')
    }
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