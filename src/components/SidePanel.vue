<template>
  <div id="side-panel-box">
    <div id="side-panel-avatar-box">
      <el-tooltip effect="dark" content="关于">
        <div id="side-panel-avatar">
          <el-avatar :src=logo size="large"/>
        </div>
      </el-tooltip>
    </div>
    <el-tree id="side-panel-tree">
    </el-tree>
  </div>
</template>

<script>
import {defineComponent} from 'vue'
import {ElAvatar, ElTree, ElTooltip} from 'element-plus'
import logo from '@/assets/logo.svg'

export default defineComponent({
  name: 'SidePanel',
  components: {
    ElAvatar,
    ElTree,
    ElTooltip
  },
  setup() {
    return {
      logo
    }
  }
})
</script>

<style>
#side-panel-avatar {
  align-content: center;
  padding-top: 25px;
  padding-bottom: 25px;
}

#side-panel-box {
  display: flow;
  width: 160px;
  height: 100vh;
}

#side-panel-avatar-box {
  width: 160px;
  height: 120px;
  background: gray;
}

#side-panel-tree {
  width: 160px;
  height: calc(100vh - 120px);
  background: gray;
}

</style>