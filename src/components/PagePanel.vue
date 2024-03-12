<template>
  <div class="page-panel-box">
    <el-tabs type="border-card" class="page-box" :closable=true>
      <el-tab-pane label="Welcome">
      </el-tab-pane>
    </el-tabs>
  </div>
</template>

<script>
import {defineComponent} from 'vue';
import {ElTabs} from 'element-plus'

export default defineComponent({
  components: {
    ElTabs
  }
})
</script>

<style>
.page-panel-box {
  width: 100%;
  height: 100%;
}

.page-box {
  width: 100%;
  height: 100%;
}
</style>