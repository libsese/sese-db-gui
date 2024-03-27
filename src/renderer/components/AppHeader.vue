<script setup lang="ts">
import {ElButton} from 'element-plus'
import {ref} from "vue";

const connect_type = ref('primary')
const connect_text = ref('+')

defineProps({
  connect_callback: {
    type: Function,
    default: () => {
    }
  }
})

defineExpose({
  connect_text,
  connect_type
})

</script>

<template>
  <div class="app-header-box">
    <el-button :type="connect_type" class="app-button" v-on:click="() => connect_callback()">
      {{ connect_text }}
    </el-button>
  </div>
</template>

<style scoped>
.app-header-box {
  -webkit-app-region: drag;
  display: flex;
  align-items: center;
  height: 43px;
  background: #383a42;
}

.app-button {
  height: 27px;
  margin-left: 5px;
  border: none;
  -webkit-app-region: no-drag;
}
</style>