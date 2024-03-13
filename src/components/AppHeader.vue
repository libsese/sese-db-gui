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

<script>
import {defineComponent} from 'vue'
import {ElButton} from 'element-plus'

export default defineComponent({
  name: "AppHeader",
  components: {
    ElButton
  },
  props: {
    connect_callback: Function,
    test_callback: Function
  },
  setup() {
    const connect_text = '+';

    return {
      connect_text
    }
  }
})

</script>

<style scoped>
.app-header-box {
  -webkit-app-region: drag;
  display: flex;
  align-items: center;
  height: 31px;
  background: #383a42;
}

.app-button {
  height: 20px;
  margin-left: 5px;
  border: none;
  -webkit-app-region: no-drag;
}

</style>