<template>
  <div id="app-panel">
    <div id="app-side-panel-box">
      <SidePanel ref="tree"/>
    </div>
    <div id="app-main-panel-box">
      <AppHeader :connect_callback="show_dialog" :test_callback="test"/>
      <PagePanel ref="pages">
        <TablePage ref="table" header="测试"/>
      </PagePanel>
      <ConnectDialog ref="dialog" :callback="do_connect"/>
    </div>
  </div>
</template>

<script>
import AppHeader from "@/components/AppHeader.vue";
import SidePanel from "@/components/SidePanel.vue";
import PagePanel from "@/components/PagePanel.vue"
import ConnectDialog from "@/components/ConnectDialog.vue";
import TablePage from "@/components/TablePage.vue";

export default {
  name: 'App',
  components: {
    SidePanel,
    AppHeader,
    PagePanel,
    ConnectDialog,
    TablePage
  },
  methods: {
    show_dialog() {
      this.$refs.dialog.dialog_visible = true;
      this.$refs.dialog.disable = false
    },
    do_connect() {
      this.$refs.dialog.disable = true
      console.log(this.$refs.dialog.conn_info)
    },
    test() {
      this.$refs.table.columns = [
        {
          prop: 'name',
          label: '姓名'
        },
        {
          prop: 'age',
          label: '年龄'
        },
        {
          prop: 'comment',
          label: '评论'
        }
      ]
      this.$refs.table.data = [
        {
          name: 'Kaoru',
          age: 23,
          comment: '一般'
        },
        {
          name: 'libsese',
          age: 2,
          comment: '还行'
        }, {
          name: 'sese-core',
          age: 2,
          comment: '凑合'
        }
      ]
      this.$refs.tree.data = [
        {
          id: 1,
          label: 'kaoru@127.0.0.1',
          children: [
            {
              id: 2,
              label: 'tb_user'
            },
            {
              id: 3,
              label: 'tb_pay'
            },
            {
              id: 4,
              label: 'tb_xxx'
            }
          ]
        }
      ]
    }
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  -ms-user-select: none;
  user-select: none;
  text-align: center;
  color: #2c3e50;
}

html, body {
  width: 100%;
  height: 100%;
  margin: 0;
  padding: 0;
  overflow: hidden;
}

#app-panel {
  display: flex;
  flex-direction: row;
  width: 100%;
  height: 100%;
}

#app-side-panel-box {
  width: 180px;
  height: 100vh;
}

#app-main-panel-box {
  flex: 1;
  display: flex;
  flex-flow: column;
  width: calc(100% - 180px);
  height: 100vh;
}
</style>
