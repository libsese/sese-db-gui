<script setup lang="ts">
import {ref} from 'vue'
import {ElButton} from 'element-plus'

const connect_text = ref('+')
const connect_callback = ref(function (){})
const test_callback = ref(function (){})
</script>

<template>
  <div class="app-header-box">
    <el-button type="primary" class="app-button" @click="connect_callback">
      {{ connect_text }}
    </el-button>
    <el-button type="warning" class="app-button" @click="test_callback">
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