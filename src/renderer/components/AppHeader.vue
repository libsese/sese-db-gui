<script setup lang="ts">
import {ElButton} from 'element-plus'

defineProps({
  connect_text: {
    type: String,
    default: '+'
  },
  connect_callback: {
    type: Function,
    default: () => {
    }
  },
  test_callback: {
    type: Function,
    default: () => {
    }
  }
})

</script>

<template>
  <div class="app-header-box">
    <el-button type="primary" class="app-button" v-on:click="() => connect_callback()">
      {{ connect_text }}
    </el-button>
    <el-button type="warning" class="app-button" v-on:click="() => test_callback()">
      test
    </el-button>
  </div>
</template>

<style scoped>
.app-header-box {
  -webkit-app-region: drag;
  display: flex;
  align-items: center;
  height: 37px;
  background: #383a42;
}

.app-button {
  height: 20px;
  margin-left: 5px;
  border: none;
  -webkit-app-region: no-drag;
}
</style>